#include <stdio.h>
#include <string.h>

struct FileResult {
    char filename[100];
    int matches;
};

int searchFile(char *filename, char *keyword) {
    FILE *file;
    char line[500];
    int count = 0;

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Warning: Could not open file '%s'. Skipping.\n", filename);
        return -1;
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

void sortResults(struct FileResult results[], int n) {
    int i, j;
    struct FileResult temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (results[j].matches < results[j + 1].matches) {
                temp = results[j];
                results[j] = results[j + 1];
                results[j + 1] = temp;
            }
        }
    }
}

int main() {
    int choice;
    char keyword[100];
    int i;

    char *files[] = {"file1.txt", "file2.txt", "file3.txt"};
    int numFiles = 3;

    struct FileResult results[3];

    printf("================================\n");
    printf("   FileFind - Search Engine\n");
    printf("================================\n");
    printf("Tip: Make sure your files are in the same folder.\n");

    while (1) {
        printf("\n1. Search files\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter keyword to search: ");
            scanf("%s", keyword);
            printf("\nSearching %d file(s)...\n", numFiles);

            for (i = 0; i < numFiles; i++) {
                strcpy(results[i].filename, files[i]);
                results[i].matches = searchFile(files[i], keyword);
            }

            sortResults(results, numFiles);

            printf("\nResults for '%s':\n", keyword);
            printf("--------------------------------\n");

            int found = 0;
            for (i = 0; i < numFiles; i++) {
                if (results[i].matches > 0) {
                    printf("%d. %s -> %d match(es)\n", i + 1, results[i].filename, results[i].matches);
                    found = 1;
                }
            }

            if (!found) {
                printf("No matches found for '%s'\n", keyword);
            }

            printf("--------------------------------\n");

        } else if (choice == 2) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}