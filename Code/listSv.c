#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    struct Student* next;  
};


void addStudent(struct Student** head_ref) {
    struct Student* new_student = (struct Student*) malloc(sizeof(struct Student));
    struct Student* last = *head_ref;

    
    printf("Nhap stt sinh vien them moi (ID): ");
    scanf("%d", &new_student->id);
    printf("Nhap ten: ");
    scanf(" %[^\n]", new_student->name);  
    printf("Nhap tuoi: ");
    scanf("%d", &new_student->age);

    new_student->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_student;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_student;
}

void printStudents(struct Student* node) {
    if (node == NULL) {
        printf("List Empty.\n");
        return;
    }
    printf("DS Sinh vien\n");
    while (node != NULL) {
        printf("ID: %d, Ten: %s, Tuoi: %d\n", node->id, node->name, node->age);
        node = node->next;
    }
}


void deleteStudentById(struct Student** head_ref, int id) {
    struct Student* temp = *head_ref;
    struct Student* prev = NULL;

    // Nếu sinh viên cần xóa là sinh viên đầu tiên
    if (temp != NULL && temp->id == id) {
        *head_ref = temp->next;
        free(temp);
        printf("Deleted SV ID %d.\n", id);
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Not found sv ID %d.\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Deleted SV ID %d.\n", id);
}

void updateStudentById(struct Student* head, int id) {
    struct Student* temp = head;

    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Not found sv co id: %d.\n", id);
        return;
    }

    printf("Nhap ten moi: ");
    scanf(" %[^\n]", temp->name);
    printf("Nhap tuoi moi: ");
    scanf("%d", &temp->age);

}

int main() {
    struct Student* head = NULL;
    int opt, id;

    while (opt != 5) {
        printf("\n--- Quan Ly Sinh Vien ---\n");
        printf("1. Them SV moi \n");
        printf("2. Xoa Sinh vien theo ID\n");
        printf("3. Cap nhat thong tin SV theo ID\n");
        printf("4. In danh sach sv\n");
        printf("5. Ket thuc\n");
        printf("Nhap tuy chon: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                addStudent(&head);
                break;
            case 2:
                printf("Nhap ID SV can xoa: ");
                scanf("%d", &id);
                deleteStudentById(&head, id);
                break;
            case 3:
                printf("Nhap ID SV can update: ");
                scanf("%d", &id);
                updateStudentById(head, id);
                break;
            case 4:
                printStudents(head);
                break;
            case 5:
                printf("Ket thuc.\n");
                break;
            default:
                printf("Wrong syntax, please input again.\n");
        }
    }

    return 0;
}