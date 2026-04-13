#include <stdio.h>
#include <string.h>

int main() {
    int choice;
    char keyword[100];

    printf("================================\n");
    printf("   Local File Search Engine\n");
    printf("================================\n");

    while (1) {
        printf("\n1. Search files\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter keyword to search: ");
            scanf("%s", keyword);
            printf("Searching for: %s\n", keyword);
        } else if (choice == 2) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}