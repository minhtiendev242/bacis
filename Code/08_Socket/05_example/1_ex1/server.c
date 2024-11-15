#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[1024] = {0};
    
    // Tạo socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)  // return -1 if error ( why==0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Gắn socket vào địa chỉ và cổng
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Server đang lắng nghe...\n");

    // Lắng nghe kết nối từ client
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    int len = sizeof(address);
    // Chấp nhận kết nối từ client
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&len)) < 0) //fix loi cu (socklen *)&add -> ... &sizeof(add)
    {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Nhận và gửi dữ liệu
    read(new_socket, buffer, 1024);
    printf("Client gửi: %s\n", buffer);
    send(new_socket, "Chào từ server!", strlen("Chào từ server!"), 0);

    // Đóng kết nối
    close(new_socket);
    close(server_fd);

    return 0;
}