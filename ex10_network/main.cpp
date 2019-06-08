#include <iostream>

#include <string>
#include <thread>
#include <functional>

#include "client.hpp"
#include "server.hpp"
#include "share.hpp"

//Example of standard output:
void output(const std::string& s) {
    std::cout << s;
}

//Example of standard input with arg:
std::string input(const char* msg = 0) {
    if (msg)
        std::cout << msg;
    std::string choice;
    std::getline(std::cin, choice);
    return choice;
}

void client_example(const char* ipAddress, const char* port) {
    my::Client client{ ipAddress,port };
    client.setLog(output);
    client.start();
    client.connect();
    client.listen();
    my::Share<std::string> message;
    bool running = true;
    output("Starting Client\n");
    //Input command and message processing on main thread:
    std::function<void(void)> in = [&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        while (running) {
            message.set(input());
            client.send(message.get());
            if (message == "exit")
                running = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    };
    std::thread thread(in);
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        if (message == "exit")
            running = false;
    }
    for (std::size_t i = 0; i < 5; ++i) {
        std::cout << ". ";
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    thread.join();
}

void server_example(const char* port) {
    my::Server server(port);
    server.setLog(output);
    server.start();
    server.bind();
    server.accept();
    server.listen();
    my::Share<std::string> message;
    my::Share<bool> running{ true };
    //Input command on sub thread:
    std::function<void(void)> in = [&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        while (running) {
            message.set(input());
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    };
    std::thread thread(in);
    //Message processing on main thread:
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        if (message == "exit")
            running = false;
    }
    thread.join();
}

int main() {
    std::string choice{ input("Client or Server: ") };
    if (choice == "Client")
        client_example("127.0.0.1", "5000");
    else if (choice == "Server")
        server_example("5000");
    else
        std::cout << "Invalid Choice\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return 0;
}