#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    // ایجاد سوکت UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "خطا در ایجاد سوکت" << std::endl;
        return 1;
    }

    // تنظیمات آدرس سرور
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // اتصال سوکت به پورت مشخص‌شده
    if (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "خطا در bind کردن سوکت" << std::endl;
        close(sock);
        return 1;
    }

    std::cout << "سرور آماده دریافت پیام است..." << std::endl;

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t recvLen = recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddr, &addrLen);
        if (recvLen > 0) {
            std::cout << "پیام دریافت شد: " << buffer << std::endl;
        }
    }

    close(sock);
    return 0;
}
