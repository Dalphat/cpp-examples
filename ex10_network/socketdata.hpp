#ifndef SOCKETDATA_HPP
#define SOCKETDATA_HPP

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "share.hpp"
#include "output.hpp"


namespace my {
    class SocketData : public Output {
    private:
        WSADATA wsaData;
    public:
        Share<bool> started;
        SocketData() : started{ false } { }
        ~SocketData() { stop(); }
        void start() {
            if (!started) {
                // Initialize Winsock
                int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
                // Returns 0 if successful, else failed with error.
                if (iResult) {
                    log("WSAStartup failed with error: ", iResult, '\n');
                    return;
                }
                started = true;
            }
        }
        void stop() {
            if (started)
                WSACleanup();
        }
        explicit operator bool() {
            return started.get();
        }
    };
}


#endif // !SOCKETDATA_HPP
