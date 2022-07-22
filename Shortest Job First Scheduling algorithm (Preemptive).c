#include<stdio.h>
#define mx 1000000009
struct process{
    int id, at, bt; /// id = Process Number || at = Arrival Time || bt = Burst Time
};
void Bubble_Sort(struct process p[], int n)
{
    int i, j;
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(p[j].at > p[j+1].at)
            {
                /// This is just swapping
                struct process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}
int main()
{
    int n;
    printf("Enter number of process: ");
    scanf("%d", &n);
    struct process p[n];
    int BT[n];
    printf("\nEnter Arrival Time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].at);
    }
    int cnt = 0;
    printf("\nEnter Burst Time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].bt);
        cnt += p[i].bt;
        BT[i] = p[i].bt;
        p[i].id = i;
    }
    Bubble_Sort(p, n);

    int gant[cnt], ct[n], wt[n], tat[n], vis[n], tim = 0, cur = -1, idx = 0;
    for(int i=0; i<n; i++) vis[i] = 0;
    for(int i=0; i<cnt; i++)
    {
        struct process take;
        take.at = mx, take.bt = mx, take.id = -1;
        int ind = -1;
        for(int j=0; j<n; j++)
        {
            if(vis[j] == 1) continue;

            if(p[j].at <= i)
            {
                if(take.bt > p[j].bt)
                {
                    take = p[j];
                    ind = j;
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
                    ind = j;
                }
                else if(take.at == p[j].at)
                {
                    if(take.bt > p[j].bt)
                    {
                        take = p[j];
                        ind = j;
                    }
                }

            }
        }
        if(take.id != cur)
        {
            cur = take.id;
            gant[idx] = cur;
            p[ind].bt--;
            if(p[ind].bt == 0)
            {
                vis[ind] = 1;
            }
            idx++;
        }
        else
        {
            p[ind].bt--;
            if(p[ind].bt == 0)
            {
                vis[ind] = 1;
            }
        }
        ct[cur] = i+1;
        tat[cur] = ct[cur]-p[cur].at;
    }
    float waiting_time = 0, turn_around_time = 0;
    for(int i=0; i<n; i++)
    {
        tat[i] = ct[i]-p[i].at;
        wt[i] = tat[i]-BT[i];
        waiting_time += wt[i];
        turn_around_time += tat[i];
    }
    printf("\nGantt Chart: ");
    for(int i=0; i<idx; i++)
    {
        printf("P%d", gant[i]+1);
        i == idx-1 ? printf("\n") : printf("->");
    }

    printf("\nAverage Waiting Time: %0.5f", waiting_time/n);
    printf("\nAverage Turn Around Time: %0.5f\n", turn_around_time/n);
}
