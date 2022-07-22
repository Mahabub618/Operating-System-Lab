#include<stdio.h>
struct process
{
    int id, at, bt;
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
    int ct[n], tat[n];
    printf("\nEnter Arrival time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].at);
    }
    printf("\nEnter Burst time: ");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &p[i].bt);
        p[i].id = i+1;
    }
    Bubble_Sort(p, n);

    printf("\nGantt chart: ");
    int tim = 0;
    float waiting_time = 0, turn_around_time = 0;
    for(int i=0; i<n; i++)
    {
        printf("P%d", p[i].id);
        if(i==0)
        {
            tim = p[i].bt;
            ct[i] = tim;
            tat[i] = ct[i]-p[i].at;
        }

        else
        {
            if(p[i].at > tim) tim += (p[i].at - tim);
            tim += p[i].bt;
            ct[i] = tim;
            tat[i] = ct[i]-p[i].at;
        }
        turn_around_time += tat[i];
        waiting_time += (tat[i]-p[i].bt);
        i == n-1? printf("\n"):printf("->");
    }
    printf("\nAverage Waiting Time: %0.5f", waiting_time/n);
    printf("\nAverage Turn Around Time: %0.5f\n", turn_around_time/n);

}
