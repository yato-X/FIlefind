#include <stdio.h>
#include <string.h>

int searchFile(char *filename, char *keyword) {
    FILE *file;
    char line[500];
    int count = 0;

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open file: %s\n", filename);
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *pos = line;
        while ((pos = strstr(pos, keyword)) != NULL) {
            count++;
            pos++;
        }
    }

    fclose(file);
    return count;
}

int main() {
    int choice;
    char keyword[100];
    char filename[100];
    int matches;

    printf("================================\n");
    printf("   Local File Search Engine\n");
    printf("================================\n");

    while (1) {
        printf("\n1. Search files\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter filename to search: ");
            scanf("%s", filename);
            printf("Enter keyword to search: ");
            scanf("%s", keyword);
            matches = searchFile(filename, keyword);
            printf("Found %d match(es) of '%s' in %s\n", matches, keyword, filename);
        } else if (choice == 2) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}