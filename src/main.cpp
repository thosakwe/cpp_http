#include <cstring>
#include <exception>
#include <iostream>
#include "server/serve-main.h"

int main(int argc, char **argv) {
    try {
        int concurrency = 1, port = 8080;

        for (int i = 0; i < argc; i++) {
            char *str = argv[i];

            if (i < argc - 1) {
                if (!strcmp("-j", str) || !strcmp("--concurrency", str)) {
                    concurrency = atoi(argv[i + 1]);
                    i++;
                } else if (!strcmp("-p", str) || !strcmp("--port", str)) {
                    port = atoi(argv[i + 1]);
                    i++;
                }
            }
        }

        return serveMain(concurrency, port);
    } catch (const std::exception &exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }
}