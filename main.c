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
    int matches;
    int i;

    char *files[] = {"file1.txt", "file2.txt", "file3.txt"};
    int numFiles = 3;

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
            printf("\nResults for '%s':\n", keyword);
            printf("--------------------------------\n");

            for (i = 0; i < numFiles; i++) {
                matches = searchFile(files[i], keyword);
                if (matches > 0) {
                    printf("%s -> %d match(es)\n", files[i], matches);
                } else {
                    printf("%s -> no matches\n", files[i]);
                }
            }

        } else if (choice == 2) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}