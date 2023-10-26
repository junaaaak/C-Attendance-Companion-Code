#include <stdio.h>
#include <string.h>

#define MAX_SUBJECTS 5

// Structure to store subject information
struct Subject {
    char name[50];
    int totalClasses;
    int presentClasses;
    double percentage;
};

int main() {
    struct Subject subjects[MAX_SUBJECTS];
    int choice;
    int numSubjects;
    double requiredPercentage;
    double overallPercentage = 0;
    int overallClassesRequired = 0;

    // Input the required attendance percentage for all subjects
    printf("Enter the required attendance percentage: ");
    scanf("%lf", &requiredPercentage);

    // Input the number of subjects
    printf("Enter the number of subjects: ");
    scanf("%d", &numSubjects);

    // Input attendance data for each subject
    for (int i = 0; i < numSubjects; i++) {
        printf("Subject %d:\n", i + 1);
        printf("Enter the name of the subject: ");
        scanf("%s", subjects[i].name);

        printf("Enter total number of classes conducted: ");
        scanf("%d", &subjects[i].totalClasses);

        int validInput = 0;
        while (!validInput) {
            printf("Enter the number of classes you have attended: ");
            scanf("%d", &subjects[i].presentClasses);

            if (subjects[i].presentClasses > subjects[i].totalClasses) {
                printf("Error: Classes attended cannot be greater than classes conducted for %s.\n", subjects[i].name);
            } else {
                validInput = 1;
            }
        }

        // Calculate the initial percentage for each subject
        subjects[i].percentage = ((double)subjects[i].presentClasses / subjects[i].totalClasses) * 100.0;
    }

    while (1) {
        // Display the menu options
        printf("\nAttendance Companion Menu:\n");
        printf("1. Calculate Attendance Percentage for a Subject\n");
        printf("2. Calculate Required Classes to Meet Percentage for a Subject\n");
        printf("3. Calculate Overall Attendance Percentage\n");
        printf("4. Calculate Overall Classes Required\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int subjectIndex;
        switch (choice) {
            case 1:
                // Calculate and display the attendance percentage for a specific subject
                printf("Enter subject index (0 to %d): ", numSubjects - 1);
                scanf("%d", &subjectIndex);

                if (subjectIndex < 0 || subjectIndex >= numSubjects) {
                    printf("Invalid subject index.\n");
                } else {
                    printf("Your current attendance percentage for %s is: %.2lf%%\n", subjects[subjectIndex].name, subjects[subjectIndex].percentage);
                }
                break;

            case 2:
                // Calculate and display the required classes to meet the percentage for a specific subject
                printf("Enter subject index (0 to %d): ", numSubjects - 1);
                scanf("%d", &subjectIndex);

                if (subjectIndex < 0 || subjectIndex >= numSubjects) {
                    printf("Invalid subject index.\n");
                } else {
                    if (subjects[subjectIndex].percentage >= requiredPercentage) {
                        printf("You already meet or exceed the required percentage for %s.\n", subjects[subjectIndex].name);
                    } else {
                        int classesNeeded = 0;
                        while (subjects[subjectIndex].percentage < requiredPercentage) {
                            subjects[subjectIndex].presentClasses++;
                            subjects[subjectIndex].totalClasses++;
                            subjects[subjectIndex].percentage = ((double)subjects[subjectIndex].presentClasses / subjects[subjectIndex].totalClasses) * 100.0;
                            classesNeeded++;
                        }
                        printf("You need to attend at least %d more classes for %s to meet the required percentage.\n", classesNeeded, subjects[subjectIndex].name);
                    }
                }
                break;

            case 3:
                // Calculate and display the overall attendance percentage for all subjects
                for (int i = 0; i < numSubjects; i++) {
                    overallPercentage += (subjects[i].percentage / numSubjects);
                }
                printf("Your overall attendance percentage for all subjects is: %.2lf%%\n", overallPercentage);
                break;

            case 4:
                // Calculate and display the overall classes required to meet the required percentage for all subjects
                for (int i = 0; i < numSubjects; i++) {
                    while (subjects[i].percentage < requiredPercentage) {
                        subjects[i].presentClasses++;
                        subjects[i].totalClasses++;
                        subjects[i].percentage = ((double)subjects[i].presentClasses / subjects[i].totalClasses) * 100.0;
                        overallClassesRequired++;
                    }
                }
                printf("You need to attend at least %d more classes overall to meet the required percentage for all subjects.\n", overallClassesRequired);
                break;

            case 5:
                // Exit the program
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                // Handle invalid input
                printf("Invalid choice. Please select a valid option.\n");
        }
    }

    return 0;
}
