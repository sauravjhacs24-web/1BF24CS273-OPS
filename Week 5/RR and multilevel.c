#include <stdio.h>

struct Process {
    int pid, at, bt, type;
    int ct, tat, wt;
};

void sort(struct Process p[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], sys[n], user[n];
    int sc = 0, uc = 0;

    for(int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        p[i].pid = i + 1;

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Enter Type (1-System / 0-User): ");
        scanf("%d", &p[i].type);

        if(p[i].type == 1)
            sys[sc++] = p[i];
        else
            user[uc++] = p[i];
    }

    sort(sys, sc);
    sort(user, uc);

    int time = 0;

    for(int i = 0; i < sc; i++) {
        if(time < sys[i].at)
            time = sys[i].at;

        time += sys[i].bt;
        sys[i].ct = time;
        sys[i].tat = sys[i].ct - sys[i].at;
        sys[i].wt = sys[i].tat - sys[i].bt;
    }

    for(int i = 0; i < uc; i++) {
        if(time < user[i].at)
            time = user[i].at;

        time += user[i].bt;
        user[i].ct = time;
        user[i].tat = user[i].ct - user[i].at;
        user[i].wt = user[i].tat - user[i].bt;
    }

    printf("\n--- System Processes (High Priority) ---\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for(int i = 0; i < sc; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
        sys[i].pid, sys[i].at, sys[i].bt,
        sys[i].wt, sys[i].tat);
    }

    printf("\n--- User Processes (Low Priority) ---\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for(int i = 0; i < uc; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
        user[i].pid, user[i].at, user[i].bt,
        user[i].wt, user[i].tat);
    }

    float total_wt = 0, total_tat = 0;
    for(int i = 0; i < sc; i++) {
        total_wt += sys[i].wt;
        total_tat += sys[i].tat;
    }
    for(int i = 0; i < uc; i++) {
        total_wt += user[i].wt;
        total_tat += user[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
