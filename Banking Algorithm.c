#include<stdio.h>

int main()
{
    int n, m;
    printf("Enter number of process: ");
    scanf("%d", &n);
    printf("\nEnter number of resource: ");
    scanf("%d", &m);
    int flag[n], need[n][m], Max[n][m], allocation[n][m], available[m];
    for(int i=0; i<n; i++) flag[i] = 0;
    printf("\nEnter number of allocated resource for each process: ");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("\nEnter number of Max need of resource for each process: ");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            scanf("%d", &Max[i][j]);
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            need[i][j] = Max[i][j] - allocation[i][j];
        }
    }
    printf("\nEnter the available resource of each process: ");
    for(int i=0; i<m; i++)
    {
        scanf("%d", &available[i]);
    }

    int sequence[n], deadLock = 0;
    for(int k=0; k<n; k++)
    {
        int ind = -1;
        for(int i=0; i<n; i++)
        {
            if(flag[i]) continue;
            for(int j=0; j<m; j++)
            {
                if(need[i][j] <= available[j])
                {
                    if(j==m-1)
                    {
                        ind = i;
                        break;
                    }
                }
                else break;
            }
            if(ind != -1) break;
        }

        if(ind == -1)
        {
            deadLock = 1;
            break;
        }
        else
        {
            flag[ind] = 1;
            sequence[k] = ind;
            for(int j=0; j<m; j++)
            {
                available[j] += allocation[ind][j];
            }
        }
    }
    if(deadLock)
    {
        printf("\nThe system is in unsafe state.");
    }
    else
    {
        printf("\nThe system is in safe state.");
        printf("\nThe safe sequence is: ");
        for(int i=0; i<n; i++)
        {
            printf("P%d", sequence[i]);
            if(i==n-1) printf("\n");
            else printf("->");
        }
    }
}
