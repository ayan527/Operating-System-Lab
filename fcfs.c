#include<stdio.h>
#include<conio.h>

void displayProcessTable(int number, int processes[], int arrival_time[], int burst_time[], int priority[], int wait_time[], int turn_around_time[]) {
	printf("Processes\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurn-Around Time\n");
	int i;
	for (i = 0; i < number; i++) {
		printf(" %d ",processes[i]);
		printf("	 \t%d ", burst_time[i] );
		printf("	 \t%d ", arrival_time[i]);
		printf("	 \t%d ", priority[i] );
		printf("	 \t%d ", wait_time[i] );
		printf("	 \t%d\n",turn_around_time[i] );
	}
}

void displayAvgTime(int number, int wait_time[], int turn_around_time[]) {
	float avg_wait_time, avg_turn_around_time;
	int total_wait_time = 0;
	int total_turn_around_time = 0;
	
	int i;
	for(i = 0; i < number; i++) {
		total_wait_time += wait_time[i];
		total_turn_around_time += turn_around_time[i];
	}
	
	avg_wait_time = (float)total_wait_time / (float)number;
	avg_turn_around_time = (float)total_turn_around_time / (float)number;
	
	printf("\nAverage Waiting Time: %f",avg_wait_time);
	printf("\nAverage Turn-Around Time: %f ",avg_turn_around_time);
}

void calculateTurnAroundTime(int number, int burst_time[], int wait_time[], int turn_around_time[]) {
	int i;
	for(i = 0; i < number; i++) {
		turn_around_time[i] = burst_time[i] + wait_time[i];
	}
}

void calculateWaitTimeFcfs(int number, int arrival_time[], int burst_time[], int wait_time[], int start_time[]) {
	start_time[0] = 0 + arrival_time[0];
	wait_time[0] = 0;
	
	int i;
	for(i = 1; i < number; i++) {
		start_time[i] = start_time[i-1] + burst_time[i-1];
		wait_time[i] = start_time[i] - arrival_time[i];
		if(wait_time[i] < 0) {
			start_time[i] += -(wait_time[i]);
			wait_time[i] = 0;
		}
	}
}

void swap(int i, int j, int processes[], int burst_time[], int priority[], int arrival_time[]) {
	processes[j]=processes[j]+processes[i]-(processes[i]=processes[j]);
	priority[j]=priority[j]+priority[i]-(priority[i]=priority[j]);
	burst_time[j]=burst_time[j]+burst_time[i]-(burst_time[i]=burst_time[j]);
	arrival_time[j]=arrival_time[j]+arrival_time[i]-(arrival_time[i]=arrival_time[j]);
}

void fcfs(int number, int processes[], int burst_time[], int priority[], int arrival_time[]) {
	int start_time[number], wait_time[number], turn_around_time[number];
	
	int i, j;
	for (i = 0; i < number - 1; i++) {
		for( j = i+ 1; j < number; j++) {
			if (arrival_time[j] < arrival_time[i]) {
				swap(i, j, processes, burst_time, priority, arrival_time);
			}
		}
	}
	
	calculateWaitTimeFcfs(number, arrival_time, burst_time, wait_time, start_time);
	calculateTurnAroundTime(number, burst_time, wait_time, turn_around_time);
	
	displayProcessTable(number, processes, arrival_time, burst_time, priority, wait_time, turn_around_time);
	displayAvgTime(number, wait_time, turn_around_time);
}


void createProcessTable(int number, int processes[], int burst_time[], int priority[], int arrival_time[]) {
	int i;
	for(i = 0; i < number; i++) {
		printf("Enter Arrival-Time Burst-Time and Priority for Process %d :",i+1);
		scanf("%d",&arrival_time[i]);
		scanf("%d",&burst_time[i]);
		scanf("%d",&priority[i]);
		processes[i]=i+1;
	}
}

int main() {
	int number, choice;
	printf("\nEnter number of processes: ");
	scanf("%d",&number);
	
	int processes[number], burst_time[number], priority[number], arrival_time[number];
	createProcessTable(number, processes, burst_time, priority, arrival_time);
	
	fcfs(number, processes, burst_time, priority, arrival_time);
	
	return 0;
}

