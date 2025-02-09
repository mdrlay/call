#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define PORT 12345
#define SERVER_IP "192.168.1.106"  // آدرس سرور را تغییر بده
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in serverAddr;
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
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);  // آدرس IP سرور

    std::cout << "کلاینت آماده ارسال داده به سرور" << std::endl;

    // ارسال داده به سرور در حلقه
    while (true) {
        std::cout << "یک پیام وارد کنید: ";
        std::cin.getline(buffer, BUFFER_SIZE);

        // ارسال داده‌ها به سرور
        ssize_t sendLen = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        if (sendLen < 0) {
            std::cerr << "خطا در ارسال داده" << std::endl;
            close(sock);
            return 1;
        }

        std::cout << "داده ارسال شد: " << buffer << std::endl;
    }

    close(sock);
    return 0;
}
