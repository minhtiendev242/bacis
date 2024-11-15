#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char *message = "Xin chào từ client UDP!";
    char buffer[1024];

    // Tạo socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket tạo thất bại");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Chuyển đổi địa chỉ IP sang dạng binary
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Địa chỉ không hợp lệ");
        return -1;
    }

    // Gửi dữ liệu đến server
    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Dữ liệu gửi đến server: %s\n", message);

    // Nhận phản hồi từ server
    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
    buffer[n] = '\0';
    printf("Nhận từ server: %s\n", buffer);

    close(sockfd);
    return 0;
}