#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080

void *handle_client(void *socket_desc) {
    int sock = (int)socket_desc;
    char buffer[1024] = {0};

    // Nhận dữ liệu từ client
    read(sock, buffer, 1024);
    printf("Nhận từ client: %s\n", buffer);
    
    // Gửi dữ liệu phản hồi lại client
    send(sock, "Chào từ server", strlen("Chào từ server"), 0);
    
    // Đóng kết nối
    close(sock);
    free(socket_desc);
    return NULL;
}

int main() {
    int server_fd, new_socket, *new_sock;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    
    // Tạo socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
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

    // Lắng nghe kết nối từ client
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server đang lắng nghe...\n");

    // Chấp nhận các kết nối
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) > 0) {
        printf("Kết nối mới từ client\n");
        
        // Tạo thread để xử lý mỗi kết nối
        new_sock = malloc(1);
        *new_sock = new_socket;
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void*)new_sock) < 0) {
            perror("Không thể tạo thread");
            return 1;
        }
    }

    if (new_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    close(server_fd);
    return 0;
}