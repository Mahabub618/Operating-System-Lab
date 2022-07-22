#include<stdio.h>
#define inf 100000009
struct process{
    int id, at, pr, bt; /// id = Process Number || at = Arrival Time || bt = Burst Time
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
    int vis[n], BT[n];
    printf("\nEnter Arrival Time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].at);
        p[i].id = i;
        vis[i] = 0;
    }
    printf("\nEnter Priority: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].pr);
    }
    int cnt = 0;
    printf("\nEnter Burst Time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].bt);
        BT[i] = p[i].bt;
        cnt += p[i].bt;
    }
    Bubble_Sort(p, n);
    int gant[cnt], ct[n], tat[n], wt[n], ind = -1, cur = -1, tim = 0, idx = 0;
    for(int i=0; i<n; i++)
    {
        struct process take;
        take.pr = inf;
        for(int j=0; j<=i; j++)
        {
            if(vis[j] == 1) continue;

            if(take.pr > p[j].pr)
            {
                take = p[j];
                ind = j;
            }
        }
        int mn = p[ind].bt;
        int mx = inf;
        if(i+1 < n) mx = p[i+1].at - p[i].at;
        if(mn > mx) mn = mx;
        tim += mn;
        if(take.id != cur)
        {
            cur = take.id;
            gant[idx] = cur;
            p[ind].bt -= mn;
            idx++;
        }
        else
        {
            p[ind].bt -= mn;
        }
        if(p[ind].bt == 0) vis[ind] = 1;
        ct[cur] = tim;
    }

    for(int i=0; i<n; i++)
    {
        struct process take;
        take.pr = inf;
        ind = -1;
        for(int j=0; j<n; j++)
        {
            if(vis[j] == 1) continue;
            if(take.pr > p[j].pr)
            {
                take = p[j];
                ind = j;
            }
        }
        if(ind != -1)
        {
            gant[idx] = take.id;
            tim += take.bt;
            vis[ind] = 1;
            ct[take.id] = tim;
            idx++;
        }
    }
    float waiting_time = 0, turn_around_time = 0;
    for(int i=0; i<n; i++)
    {
        tat[i] = ct[i]-p[i].at;
        wt[i] = tat[i]-BT[i];
        waiting_time += wt[i];
        turn_around_time += tat[i];
    }
    for(int i=0; i<idx; i++)
    {
        printf("P%d", gant[i]+1);
        i == idx-1 ? printf("\n") : printf("->");
    }
    printf("\nAverage Waiting Time: %0.5f", waiting_time/n);
    printf("\nAverage Turn Around Time: %0.5f\n", turn_around_time/n);
}
