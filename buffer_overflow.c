#include <stdio.h>
int main(void) {
    char password[8];
    int access = 0;

    fgets(password, 10, stdin);

    if (access) {
        printf("Welcome root user");
    } else {
        printf("Access denied");
    }

    return 0;
}