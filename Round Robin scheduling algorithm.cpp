#include<bits/stdc++.h>
using namespace std;
#define inf 1000000009
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
    int n, nn;
    printf("Enter number of process: ");
    scanf("%d", &n);
    nn = n;
    struct process p[n];
    int wt[n], ct[n], tat[n], BT[n], qt;
    printf("\nEnter Arrival Time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].at);
    }
    printf("\nEnter Burst Time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].bt);
        BT[i] = p[i].bt;
        p[i].id = i;
    }
    printf("\nEnter Time Quantum: ");
    scanf("%d", &qt);

    Bubble_Sort(p, n);
    int gant[n*qt],  sum = 0, i = 0, idx = 0, flag = 0;
    float waiting_time = 0, turn_around_time = 0;

    queue<process> q;
    q.push(p[0]);
    while(nn > 0)
    {
        struct process fr = q.front();
        q.pop();

        for(int tim = 1; tim <= qt and fr.bt>0; tim++)
        {
            for(int i=0; i<n; i++)
            {
                if(p[i].at == sum and p[i].id != fr.id) q.push(p[i]);
            }
            fr.bt--;
            sum++;
        }
        if(fr.bt != 0) q.push(fr);
        else
        {
            nn--;
            tat[fr.id] = sum-fr.at;
            wt[fr.id] = tat[fr.id]-BT[fr.id];
            waiting_time += wt[fr.id];
            turn_around_time += tat[fr.id];
        }
        gant[idx] = fr.id;
        idx++;
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
