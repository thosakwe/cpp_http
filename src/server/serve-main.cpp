#include "serve-main.h"

class WithSocket {
private:
    int socket = -1;
public:
    ~WithSocket() {
        if (socket != -1)
            close(socket);
    }

    void setSocket(int socket) {
        this->socket = socket;
    }
};

void handleClient(int client) {
    std::string str;
    std::time_t rawtime;
    std::tm *timeinfo;
    char timebuf[80];

    // Format date
    std::time(&rawtime);
    timeinfo = std::gmtime(&rawtime);
    // Tue, 15 Nov 1994 08:12:31 GMT
    strftime(timebuf, 80, "%a, %d %b %G %H:%M:%S GMT", timeinfo);

    // Send 200
    std::stringstream response;
    response << "HTTP/1.1 200 OK\r\n";
    response << "Date: " << timebuf << "\r\n";
    response << "Content-Type: text/html; charset=utf-8\r\n";
    response << "Server: C++" << "\r\n" << "\r\n";
    response
            << "<!DOCTYPE html><html><head><title>Hello, C++ World!</title></head><body><h1>Hello, C++ World!</h1></body></html>"
            << "\r\n" << "\r\n";

    std::string r = response.str();

    if (write(client, r.c_str(), r.length()) < 0) {
        std::cerr << "Couldn't send response..." << "\r\n";
    }

    if (close(client) < 0) {
        std::cerr << "Couldn't close client socket..." << "\r\n";
    }
}

int serveMain(int concurrency, int port) {
    WithSocket *ws = new WithSocket();
    int sockfd, client, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ws->setSocket(sockfd);

    if (sockfd < 0) {
        std::cerr << "Error opening socket." << std::endl;
        return 1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (::bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Couldn't bind socket." << std::endl;
        std::cerr << strerror(errno) << std::endl;
        return 1;
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    std::fprintf(stdout, "Now listening at http://localhost:%d\n", port);

    while (true) {
        client = accept(sockfd,
                        (struct sockaddr *) &cli_addr, &clilen);
        if (client < 0) {
            std::cout << "Couldn't accept client..." << std::endl;
            continue;
        }

        pid = fork();

        if (pid < 0) {
            std::cout << "Failed to fork." << std::endl;
        }

        if (pid == 0) {
            delete ws;
            handleClient(client);
            exit(0);
        } else close(client);
    }
}