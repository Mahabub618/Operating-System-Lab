#include<bits/stdc++.h>
using namespace std;
#define inf 1000000009
struct process
{
    int id, at, bt, no; /// id = Process Number || at = Arrival Time || bt = Burst Time
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
    int n, nn;
    printf("Enter number of process: ");
    scanf("%d", &n);
    nn = n;
    struct process p[n];
    queue<process> q1, q2;
    int wt[n], ct[n], tat[n], BT[n], flag[n], qt;
    printf("\nEnter Arrival Time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].at);
        flag[i] = 0;
    }
    int tot_time = 0;
    printf("\nEnter Burst Time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].bt);
        BT[i] = p[i].bt;
        p[i].id = i;
        tot_time += p[i].bt;
    }
    printf("\nEnter queue no. for each process: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].no);
    }
    printf("\nEnter Time Quantum for process-1: ");
    scanf("%d", &qt);

    Bubble_Sort(p, n);
    int gant[tot_time+1],  sum = 0, i = 0, idx = 0;
    float waiting_time = 0, turn_around_time = 0;

    for(int i=0; i<=tot_time; i++)
    {
        if(q1.empty() and q2.empty())
        {
            for(int j=0; j<n; j++)
            {
                if(p[j].at <= i and p[j].bt>0 and flag[j]==0)
                {
                    flag[j] = 1;
                    if(p[j].no == 1) q1.push(p[j]);
                    else q2.push(p[j]);
                }
            }
        }

        while(q1.size() > 0)
        {
            struct process fr = q1.front();
            q1.pop();

            for(int tim = 1; tim <= qt and fr.bt>0; tim++)
            {
                fr.bt--;
                i++;
                for(int j=0; j<n; j++)
                {
                    if(p[j].at == i and p[j].bt > 0 and flag[j] == 0)
                    {
                        flag[j] = 1;
                        if(p[j].no == 1) q1.push(p[j]);
                        else q2.push(p[j]);
                    }
                }
            }
            if(fr.bt != 0) q1.push(fr);
            else
            {
                tat[fr.id] = i-fr.at;
                wt[fr.id] = tat[fr.id]-BT[fr.id];
                waiting_time += wt[fr.id];
                turn_around_time += tat[fr.id];
            }
            gant[idx] = fr.id;
            idx++;
        }
        while(q2.size() > 0)
        {
            struct process fr = q2.front();
            q2.pop();
            while(fr.bt > 0)
            {
                fr.bt--;
                i++;
                for(int j=0; j<n; j++)
                {
                    if(p[j].at == i and p[j].bt > 0 and flag[j] == 0)
                    {
                        flag[j] = 1;
                        if(p[j].no == 1) q1.push(p[j]);
                        else q2.push(p[j]);
                    }
                }
                if(q1.size() > 0) break;
            }
            if(fr.bt == 0)
            {
                printf("I = %d\n", i);
                tat[fr.id] = i-fr.at;
                wt[fr.id] = tat[fr.id]-BT[fr.id];
                waiting_time += wt[fr.id];
                turn_around_time += tat[fr.id];
            }
            else q2.push(fr);
            gant[idx] = fr.id;
            idx++;
            if(q1.size() > 0)
            {
                i--;
                break;
            }
        }
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
