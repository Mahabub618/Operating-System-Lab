#include<stdio.h>
#define mx 1000000009
struct process{
    int id, at, bt; /// id = Process Number || at = Arrival Time || bt = Burst Time
};
int main()
{
    int n;
    printf("Enter the number of process: ");
    scanf("%d", &n);
    struct process p[n];

    printf("\nEnter Arrival time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].at);
    }
    printf("\nEnter Burst time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].bt);
        p[i].id = i;
    }

    int gant[n], ct[n], tat[n], vis[n], wt[n];

    for(int i=0; i<n; i++)
    {
        vis[i] = 0;
    }
    int tim = 0;
    for(int i=0; i<n; i++)
    {
        struct process take;
        take.at = mx, take.bt = mx, take.id = -1;

        for(int j=0; j<n; j++)
        {
            if(vis[j] == 1) continue;

            if(p[j].at <= tim)
            {
                if(take.bt > p[j].bt)
                {
                    take = p[j];
                }
            }

        }

        if(take.id == -1)
        {
            for(int j=0; j<n; j++)
            {
                if(vis[j] == 1) continue;

                if(take.at > p[j].at)
                {
                    take = p[j];
                }
                else if(take.at == p[j].at)
                {
                    if(take.bt > p[j].bt)
                    {
                        take = p[j];
                    }
                }

            }
        }

        gant[i] = take.id;
        tim += take.bt;
        vis[take.id] = 1;
        ct[take.id] = tim;
        tat[take.id] = ct[take.id]-take.at;
        wt[take.id] = tat[take.id]-take.bt;
    }
    float waiting_time = 0, turn_around_time = 0;
    printf("\nGantt Chart: ");
    for(int i=0; i<n; i++)
    {
        printf("P%d", gant[i]+1);
        waiting_time += wt[i];
        turn_around_time += tat[i];

        i == n-1 ? printf("\n") : printf("->");
    }
    printf("\nAverage Waiting Time: %0.5f", waiting_time/n);
    printf("\nAverage Turn Around Time: %0.5f\n", turn_around_time/n);
}
