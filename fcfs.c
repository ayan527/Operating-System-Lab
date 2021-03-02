#include<stdio.h>
#include<conio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[])
{
	int i;
	int st[n];
	st[0] = 0;
	wt[0] = 0;
	for (i = 1; i < n ; i++ ){
		st[i] = st[i-1] + bt[i-1];
		wt[i] = st[i] - at[i];
		if(wt[i] < 0) {
			st[i] += -(wt[i]);
			wt[i] = 0;
		}
	}
}
void findTurnAroundTime( int processes[], int n, int bt[], int wt[], int tat[])
{
	int i;
	for (i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}
void findavgTime( int processes[], int n, int bt[], int at[])
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0, i;
	findWaitingTime(processes, n, bt, wt, at);
	findTurnAroundTime(processes, n, bt, wt, tat);
	printf("Processes\tBurst Time\tArrival Time\tWaiting time\tTurn around time\n");
	for (i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		printf(" %d ",(i+1));
		printf("	 \t%d ", bt[i] );
		printf("	 \t%d ", at[i] );
		printf("	 \t%d ", wt[i] );
		printf("	 \t%d\n",tat[i] );
	}
	float s=(float)total_wt / (float)n;
	float t=(float)total_tat / (float)n;
	printf("Average waiting time = %f",s);
	printf("\n");
	printf("Average turn around time = %f ",t);
}
int main()
{
	int n;
	printf("Enter Total Process:\t "); 
  	scanf("%d",&n);
	int i, processes[n], burst_time[n], arrival_time[n];
	for(i=0;i<n;i++)
	{
		printf("Enter Burst Time and Arrival Time for Process %d :",i+1);
		scanf("%d",&burst_time[i]);
		scanf("%d",&arrival_time[i]);
		processes[i]=i+1;
	}
	findavgTime(processes, n, burst_time, arrival_time);
	return 0;
}

