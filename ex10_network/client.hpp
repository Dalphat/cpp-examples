#ifndef CLIENT_HPP
#define CLIENT_HPP
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <functional>
#include <mutex>

#include "share.hpp"
#include "output.hpp"
#include "socketdata.hpp"

/*
    TODO: Non blocking listener, and implement the rest of the design.
*/

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

//Simplified Utility
namespace my {
    class Client : public Output {
    protected:
        SocketData sockData;
        SOCKET ConnectSocket = INVALID_SOCKET;
        struct addrinfo* result, hints;
        static std::size_t count;
        Share<bool> connected, listening;
        std::unique_ptr<std::thread> listener;
        std::mutex listener_mutex;
        void setListening(bool b) {
            listener_mutex.lock();
            listening = b;
            listener_mutex.unlock();
        }
        Share<std::size_t> buffer_size;
        char* buffer;
    public:
        std::string ipAddress, port;
        Client(const std::string& ipAddress = std::string(), const std::string& port = std::string()) :
            ConnectSocket{ INVALID_SOCKET }, result{ NULL }, hints{},
            ipAddress{ ipAddress }, port{ port }, buffer_size { 1024 },
            connected{ false }, listening{ false }, buffer{ 0 } {
        }
        ~Client() {
            stop();
            if (buffer) {
                delete[] buffer;
                buffer = 0;
            }
        }
        void start() { sockData.start(); }
        void stop() {
            disconnect();
            sockData.stop();
        }
        void connect(int ai_family = AF_UNSPEC, int ai_socktype = SOCK_STREAM,
            int ai_protocol = IPPROTO_TCP, int ai_flags = 0) {
            if (!sockData.started)
                return;
            disconnect();
            ZeroMemory(&hints, sizeof(hints));
            hints.ai_family = ai_family;
            hints.ai_socktype = ai_socktype;
            hints.ai_protocol = ai_protocol;
            hints.ai_flags = ai_flags;
            // Resolve the server address and port
            int iResult = getaddrinfo(ipAddress.c_str(), port.c_str(), &hints, &result);
            if (iResult) {
                log("getaddrinfo failed with error: ", iResult, '\n');
                return;
            }
            // Attempt to connect to an address until one succeeds
            for (addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next) {
                // Create a SOCKET for connecting to server
                ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
                if (ConnectSocket == INVALID_SOCKET) {
                    log("socket failed with error: ", WSAGetLastError(), '\n');
                    return;
                }
                // Connect to server.
                int iResult = ::connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
                if (iResult == SOCKET_ERROR) {
                    closesocket(ConnectSocket);
                    ConnectSocket = INVALID_SOCKET;
                    continue;
                }
                break;
            }
            freeaddrinfo(result);
            if (ConnectSocket == INVALID_SOCKET) {
                log("Unable to connect to server!\n");
                return;
            }
            connected = true;
            return;
        }
        bool send(const std::string& msg) {
            bool m_state = false;
            if (connected) {
                int iResult = ::send(ConnectSocket, msg.c_str(), static_cast<int>(msg.size()), 0);
                if (iResult == SOCKET_ERROR)
                    log("send failed with error: ", WSAGetLastError(), '\n');
                else
                    m_state = true;
            }
            return m_state;
        }
        bool disconnect() {
            // shutdown the connection since no more data will be sent
            if (connected) {
                connected = false;
                shutdown(ConnectSocket, SD_BOTH);
                closesocket(ConnectSocket);
                if (isListening()) {
                    setListening(false);
                    listener->join();
                }
            }
            return true;
        }
        //Starts the listener
        void listen() {
            if (!isListening() && connected) {
                listener = std::make_unique<std::thread>([&]()->void {
                    // Receive until the peer closes the connection
                    buffer = new char[buffer_size.get()];
                    int iResult;
                    setListening(true);
                    do {
                        for (std::size_t i = 0; i < buffer_size.get(); ++i)
                            buffer[i] = '\0';
                        iResult = recv(ConnectSocket, buffer, static_cast<int>(buffer_size.get()), 0);
                        if (iResult > 0)
                            log("Received: ", buffer, '\n');
                        else if (iResult)//0
                            log("Connection closed\n");
                        else
                            log("recv failed with error: ", WSAGetLastError(), '\n');
                    } while (iResult > 0 && listening);
                });
            }
        }
        bool isListening() {
            return listening.get();
        }
    };
}
#endif // !CLIENT_HPP
