 #include <stdio.h>
#include <math.h>

struct Task {
    int id;
    float C;
    float T;
};

void sortTasks(struct Task tasks[], int n) {
    struct Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].T > tasks[j].T) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task tasks[n];
    float U = 0;


    for (int i = 0; i < n; i++) {
        printf("\nTask %d:\n", i + 1);
        tasks[i].id = i + 1;

        printf("Enter Execution Time (C%d): ", i + 1);
        scanf("%f", &tasks[i].C);

        printf("Enter Period (T%d): ", i + 1);
        scanf("%f", &tasks[i].T);

        U += (tasks[i].C / tasks[i].T);
    }


    printf("\nCPU Utilization (U) = %.4f\n", U);


    float bound = n * (pow(2, (1.0 / n)) - 1);
    printf("RMS Bound = %.4f\n", bound);

    if (U <= bound) {
        printf("Schedulable using RMS\n");
    } else {
        printf("Not guaranteed schedulable (need further analysis)\n");
    }


    sortTasks(tasks, n);

    printf("\nTask Priorities (Lower period = Higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Priority %d -> Task %d (T = %.2f)\n",
               i + 1, tasks[i].id, tasks[i].T);
    }


    printf("\nScheduling Order (One Cycle Simulation):\n");
    for (int i = 0; i < n; i++) {
        printf("Executing Task %d (C = %.2f, T = %.2f)\n",
               tasks[i].id, tasks[i].C, tasks[i].T);
    }

    return 0;
}



