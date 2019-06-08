#ifndef SERVER_HPP
#define SERVER_HPP

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")


#include "share.hpp"
#include "output.hpp"
#include "socketdata.hpp"

#include <vector>
#include <unordered_map>
#include <functional>
#include <initializer_list>
#include <sstream>

namespace my {
    class Server : public Output {
    private:
        SocketData sockData;
        SOCKET server;
        const char* port;
        struct addrinfo* result = NULL, hints;

        //Shared resource members: (Thread Safe)
        Share<bool> connected, listening, accepting;
        Share<std::size_t> buffer_size;

        std::unique_ptr<std::thread> listener, accepter;
        std::unordered_map<SOCKET, sockaddr_in> clients;

        std::mutex client_mutex;

        u_long mode;

        char* buffer;
    public:
        Server(const char* port, std::size_t buffer_size = 1024, u_long mode = 1) : 
            port{ port }, buffer_size{ buffer_size }, mode { mode }, buffer{0},
            connected{ false }, listening{ false }, accepting{ false } { 
        }
        ~Server() {
            stop();
            if (buffer) {
                delete[] buffer;
                buffer = 0;
            }
        }
        void start() { sockData.start(); }
        void stop() {
            //Attempt to disconnect all services
            disconnect();
            sockData.stop();
        }
        //Binds server to a port
        void bind(int ai_family = AF_INET, int ai_socktype = SOCK_STREAM,
            int ai_protocol = IPPROTO_TCP, int ai_flags = AI_PASSIVE) {
            if (!sockData.started)
                return;
            disconnect();
            ZeroMemory(&hints, sizeof(hints));
            hints.ai_family = ai_family;
            hints.ai_socktype = ai_socktype;
            hints.ai_protocol = ai_protocol;
            hints.ai_flags = ai_flags;
            // Resolve the server address and port
            int iResult = getaddrinfo(NULL, port, &hints, &result);
            if (iResult != 0) {
                Output::log("getaddrinfo failed with error: ", iResult, '\n');
                return;
            }
            // Create a SOCKET for connecting to server
            server = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
            if (server == INVALID_SOCKET) {
                Output::log("socket failed with error: ", WSAGetLastError(), '\n');
                freeaddrinfo(result);
                return;
            }
            // Setup the socket to non blocking
            unsigned long BLOCKING = 0, NONBLOCKING = 1;
            ioctlsocket(server, FIONBIO, &NONBLOCKING);//Defaulting to non blocking.

            // Setup the TCP listening socket
            iResult = ::bind(server, result->ai_addr, (int)result->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                Output::log("bind failed with error: ", WSAGetLastError(), '\n');
                freeaddrinfo(result);
                closesocket(server);
                return;
            }
            //std::cout << ioctlsocket(server, FIONBIO, &listen_mode) << '\n';
            connected = true;
        }
        //Disconnect to port
        void disconnect() {
            if (connected) {
                if (isAccepting()) {
                    accepting = false;
                    shutdown(server, SD_BOTH);
                    closesocket(server);
                    accepter->join();
                }
                for (auto it = clients.begin(); it != clients.end(); ++it) {
                    shutdown(it->first, SD_BOTH);
                    closesocket(it->first);
                }
                client_mutex.lock();
                clients.clear();
                client_mutex.unlock();
                if (isListening()) {
                    listening = false;
                    listener->join();
                }
                freeaddrinfo(result);
                connected = false;
            }
        }
        //Check if server is listening
        bool isListening() {
            return listening.get();
        }
        //Check if server is accepting
        bool isAccepting() {
            return accepting.get();
        }
        void accept() {
            int iResult;
            if (sockData.started && connected && !accepting) {
                accepter = std::make_unique<std::thread>([&]()->void {
                    Output::log("Accepting opening...\n");
                    accepting = true;
                    while (accepting) {
                        iResult = ::listen(server, SOMAXCONN);
                        if (iResult != SOCKET_ERROR) {
                            sockaddr_in client_addr;
                            int size = sizeof(client_addr);
                            SOCKET client = ::accept(server, reinterpret_cast<sockaddr*>(&client_addr), &size);
                            if (client != INVALID_SOCKET) {
                                char user[NI_MAXHOST];
                                Output::log(inet_ntop(AF_INET,&client_addr.sin_addr,user,NI_MAXHOST)," connected on port ",ntohs(client_addr.sin_port), '\n');
                                client_mutex.lock();
                                clients[client] = client_addr;
                                client_mutex.unlock();
                            }
                        }
                    }
                    Output::log("Accepting closing...\n");
                });
            }
        }
        void listen() {
            if (!isListening()) {
                listener = std::make_unique<std::thread>([&]()->void {
                    // Receive until the peer shuts down the connection
                    Output::log("Connection opening...\n");
                    buffer = new char[buffer_size.get()];
                    listening = true;
                    do {
                        client_mutex.lock();
                        for (auto it = clients.begin(); it != clients.end();) {
                            for (std::size_t i = 0; i < buffer_size.get(); ++i)
                                buffer[i] = '\0';
                            int iResult = recv(it->first, buffer, static_cast<int>(buffer_size.get()), 0);
                            if (iResult > 0) {
                                Output::log ("Received: ", buffer, '\n');
                                if (buffer == "exit") {
                                    shutdown(it->first, SD_SEND);
                                    closesocket(it->first);
                                    it = clients.erase(it);
                                    continue;
                                }
                                else {
                                    // Echo the buffer back to the sender
                                    int iSendResult = send(it->first, buffer, iResult, 0);
                                    if (iSendResult == SOCKET_ERROR) {
                                        Output::log("send failed with error: ", WSAGetLastError(), '\n');
                                        closesocket(it->first);
                                    }
                                }
                            }
                            ++it;
                        }
                        client_mutex.unlock();
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    } while (isListening());
                    Output::log("Connection closing...\n");
                });
            }
        }
    };
}
#endif // !SERVER_HPP
