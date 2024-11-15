#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024];

    // Tạo socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket tạo thất bại");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Gắn socket vào địa chỉ
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind thất bại");
        return -1;
    }

    printf("Server UDP đang lắng nghe...\n");

    // Nhận dữ liệu và gửi phản hồi
    while (1) {
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_len);
        if (n < 0) {
            perror("Nhận dữ liệu thất bại");
            continue;
        }
        buffer[n] = '\0';
        printf("Nhận từ client: %s\n", buffer);

        // Gửi phản hồi lại client
        sendto(sockfd, "Chào từ UDP server", strlen("Chào từ UDP server"), 0, (struct sockaddr *)&client_addr, addr_len);
    }

    close(sockfd);
    return 0;
}