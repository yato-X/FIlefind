#include <stdio.h>
#include <string.h>

// this holds the file name and how many times the word was found
struct FileResult {
    char filename[100];
    int matches;
};

// opens a file and counts how many times the keyword shows up
int searchFile(char *filename, char *keyword) {
    FILE *fp;
    char line[500];
    int count = 0;
    char *found;

    fp = fopen(filename, "r");

    // if file doesnt open just skip it
    if (fp == NULL) {
        printf("cant open %s, skipping\n", filename);
        return -1;
    }

    // go through each line
    while (fgets(line, 500, fp) != NULL) {
        found = line;
        // check if keyword is in this line
        while ((found = strstr(found, keyword)) != NULL) {
            count++;
            found++;
        }
    }

    fclose(fp);
    return count;
}

// sort files so highest matches come first
// using bubble sort because its simple
void sortResults(struct FileResult results[], int n) {
    int i, j;
    struct FileResult temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (results[j].matches < results[j+1].matches) {
                temp = results[j];
                results[j] = results[j+1];
                results[j+1] = temp;
            }
        }
    }
}

int main() {
    int choice;
    char keyword[100];
    int i;
    int total = 0;
    int found = 0;

    // these are the files we are searching through
    char *files[] = {"file1.txt", "file2.txt", "file3.txt"};
    int numFiles = 3;

    struct FileResult results[3];

    printf("================================\n");
    printf("   FileFind - Search Engine\n");
    printf("================================\n");
    printf("make sure file1.txt file2.txt file3.txt are in this folder\n");

    while (1) {
        printf("\n1. Search\n");
        printf("2. Exit\n");
        printf("choice: ");
        scanf("%d", &choice);

        if (choice == 1) {

            printf("enter keyword: ");
            scanf("%s", keyword);

            // basic check
            if (strlen(keyword) == 0) {
                printf("keyword cant be empty\n");
                continue;
            }

            printf("\nlooking for '%s' in %d files...\n", keyword, numFiles);

            total = 0;

            // search each file
            for (i = 0; i < numFiles; i++) {
                strcpy(results[i].filename, files[i]);
                results[i].matches = searchFile(files[i], keyword);

                if (results[i].matches == -1) {
                    results[i].matches = 0;
                }

                total += results[i].matches;
            }

            // sort before showing
            sortResults(results, numFiles);

            printf("\nresults for '%s':\n", keyword);
            printf("--------------------------------\n");

            found = 0;
            for (i = 0; i < numFiles; i++) {
                if (results[i].matches > 0) {
                    printf("%d. %s -- %d match(es)\n", i+1, results[i].filename, results[i].matches);
                    found = 1;
                }
            }

            if (found == 0) {
                printf("nothing found for '%s'\n", keyword);
            }

            printf("--------------------------------\n");
            printf("total: %d match(es) in %d file(s)\n", total, numFiles);

        } else if (choice == 2) {
            printf("bye!\n");
            break;
        } else {
            printf("invalid option\n");
        }
    }

    return 0;
}