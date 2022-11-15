#include<stdio.h>
#include<stdlib.h>

void findWaitingTime(int processes[], int n,int at[],
      int bt[], int wt[], int quantum)
{
  int rem_bt[n];
  for (int i = 0 ; i < n ; i++)
    rem_bt[i] = bt[i];

  int t = 0;

  while (1)
  {
    int done = 1;

    for (int i = 0 ; i < n; i++)
    {
      if (rem_bt[i] > 0)
      {
        done = 0;

        if (rem_bt[i] > quantum)
        {
          t += quantum;

          rem_bt[i] -= quantum;
        }

        else
        {
          t = t + rem_bt[i];

          wt[i] = t - bt[i]-at[i];

          rem_bt[i] = 0;
        }
      }
    quantum *=2;
    }
    
    if (done == 1)
    break;
  }
}

void findTurnAroundTime(int processes[], int n,int at[],int bt[], int wt[], int tat[])
{

  for (int i = 0; i < n ; i++)
    tat[i] = bt[i] + wt[i];
}

void findavgTime(int processes[], int n,int at[], int bt[],int quantum)
{
  int wt[n], tat[n], total_wt = 0, total_tat = 0;

  findWaitingTime(processes, n,at, bt, wt, quantum);

  findTurnAroundTime(processes, n,at, bt, wt, tat);

  printf("PN\t AT\t BT\t WT\t TAT\n");

  for (int i=0; i<n; i++)
  {
    total_wt = total_wt + wt[i];
    total_tat = total_tat + tat[i];
    printf("%d\t %d\t %d\t %d\t %d\n",i+1,at[i],bt[i],wt[i],tat[i]);
  }

  printf("Average waiting time = %f ",(float)total_wt / (float)n);
  printf("\nAverage turn around time = %f ",(float)total_tat / (float)n);
}

// Driver code
int main()
{
  int n;
  printf("enter no of process:");
  scanf("%d",&n);

  int processes[n];
  int arrival_time[n];
  int burst_time[n];

  int i=1;
  while(i<=n)
  {
    printf("enter arrival time for processes %d:",i);
    scanf("%d",&arrival_time[i-1]);
    printf("enter burst time for processes %d:",i);
    scanf("%d",&burst_time[i-1]);
    processes[i]=i++;

  }
  

  int quantum;
  printf("enter time quantum:");
  scanf("%d",&quantum);

  findavgTime(processes, n,arrival_time, burst_time, quantum);
  return 0;
}
