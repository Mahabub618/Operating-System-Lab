#include<bits/stdc++.h>
using namespace std;
#define inf 1000000009
struct process
{
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

    int wt[n], ct[n], tat[n], BT[n], flag[n], qt1, qt2;
    float turn_around_time = 0, waiting_time = 0;
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
    Bubble_Sort(p, n);

    queue<process> q1, q2, q3;
    printf("\nEnter time quantum for process-1: ");
    scanf("%d", &qt1);
    printf("\nEnter time quantum for process-2: ");
    scanf("%d", &qt2);

    for(int i=0; i<n; i++)
    {
        q1.push(p[i]);
    }
    vector<int> gant;
    int cur_time = 0;

    while(q1.size() > 0)
    {
        process fr = q1.front();
        q1.pop();
        gant.push_back(fr.id);
        for(int tim = 1; tim <= qt1 and fr.bt > 0; tim++)
        {
            fr.bt--;
            cur_time++;
        }
        if(fr.bt != 0) q2.push(fr);
        else
        {
            ct[fr.id] = cur_time;
            tat[fr.id] = ct[fr.id] - fr.at;
            wt[fr.id] = tat[fr.id] - BT[fr.id];

            turn_around_time += tat[fr.id];
            waiting_time += wt[fr.id];
        }
    }
    while(q2.size() > 0)
    {
        process fr = q2.front();
        q2.pop();
        gant.push_back(fr.id);
        for(int tim = 1; tim <= qt2 and fr.bt > 0; tim++)
        {
            fr.bt--;
            cur_time++;
        }
        if(fr.bt != 0) q3.push(fr);
        else
        {
            ct[fr.id] = cur_time;
            tat[fr.id] = ct[fr.id] - fr.at;
            wt[fr.id] = tat[fr.id] - BT[fr.id];

            turn_around_time += tat[fr.id];
            waiting_time += wt[fr.id];
        }
    }
    while(q3.size() > 0)
    {
        process fr = q3.front();
        q3.pop();
        gant.push_back(fr.id);
        cur_time += fr.bt;

        ct[fr.id] = cur_time;
        tat[fr.id] = ct[fr.id] - fr.at;
        wt[fr.id] = tat[fr.id] - BT[fr.id];

        turn_around_time += tat[fr.id];
        waiting_time += wt[fr.id];

    }

    printf("\nGantt chart: ");
    for(int i=0; i<gant.size(); i++)
    {
        printf("P%d", gant[i]+1);
        if(i == gant.size()-1)
        {
            printf("\n");
        }
        else printf("->");
    }
    printf("\nAverage Waiting Time: %0.5f", waiting_time/n);
    printf("\nAverage Turn Around Time: %0.5f\n", turn_around_time/n);
}
