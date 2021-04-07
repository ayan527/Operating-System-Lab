#include<stdio.h>
#include<conio.h>
#include<stdbool.h>

void displayProcessTable(int number, int processes[], int burst_time[], int priority[], int wait_time[], int turn_around_time[]) {
	int arrival_time = 0;
	
	printf("Processes\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurn-Around Time\n");
	int i;
	for (i = 0; i < number; i++) {
		printf(" %d ",processes[i]);
		printf("	 \t%d ", burst_time[i] );
		printf("	 \t%d ", arrival_time);
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

void calculateWaitTime(int number, int burst_time[], int wait_time[], int start_time[]) {
	start_time[0] = 0;
	wait_time[0] = 0;
	
	int i;
	for(i = 1; i < number; i++) {
		start_time[i] = start_time[i-1] + burst_time[i-1];
		wait_time[i] = start_time[i];
	}
}

void calculateTurnAroundTime(int number, int burst_time[], int wait_time[], int turn_around_time[]) {
	int i;
	for(i = 0; i < number; i++) {
		turn_around_time[i] = burst_time[i] + wait_time[i];
	}
}

void swap(int i, int j, int processes[], int burst_time[], int priority[]) {
	processes[j]=processes[j]+processes[i]-(processes[i]=processes[j]);
	priority[j]=priority[j]+priority[i]-(priority[i]=priority[j]);
	burst_time[j]=burst_time[j]+burst_time[i]-(burst_time[i]=burst_time[j]);
}

void fcfs(int number, int processes[], int burst_time[], int priority[]) {
	int start_time[number], wait_time[number], turn_around_time[number];
	
	calculateWaitTime(number, burst_time, wait_time, start_time);
	calculateTurnAroundTime(number, burst_time, wait_time, turn_around_time);
	
	displayProcessTable(number, processes, burst_time, priority, wait_time, turn_around_time);
	displayAvgTime(number, wait_time, turn_around_time);
}

void sjf(int number, int processes[], int burst_time[], int priority[]) {
	int start_time[number], wait_time[number], turn_around_time[number];
	
	int i, j;
	for (i = 0; i < number - 1; i++) {
		for( j = i+ 1; j < number; j++) {
			if ((burst_time[j] < burst_time[i]) || (burst_time[j] == burst_time[i] && processes[j] < processes[i])) {
				swap(i,j, processes, burst_time, priority, arrival_time);
			}
		}
	}
	
	calculateWaitTime(number, burst_time, wait_time, start_time);
	calculateTurnAroundTime(number, burst_time, wait_time, turn_around_time);
	
	displayProcessTable(number, processes, burst_time, priority, wait_time, turn_around_time);
	displayAvgTime(number, wait_time, turn_around_time);
}

void rr(int number, int processes[], int burst_time[], int priority[]) {
	int time_quantum, temp_burst_time[number], wait_time[number], turn_around_time[number];
	
	int i;
	for(i = 0; i < number; i++) {
		temp_burst_time[i] = burst_time[i];
	}
	
	printf("\nEnter the Time-Quantum: ");
	scanf("%d",&time_quantum);
	
	int current_time = 0;
	bool isDone = false;	
	while(!isDone) {
		isDone = true;
		
		for(i = 0; i < number; i++) {
			if (temp_burst_time[i] > 0) { 
                isDone = false;
  
                if (temp_burst_time[i] > time_quantum) { 
                    current_time += time_quantum; 
                    temp_burst_time[i] -= time_quantum; 
                } else{
                    current_time = current_time + temp_burst_time[i];
                    wait_time[i] = current_time - burst_time[i];
                    temp_burst_time[i] = 0; 
                } 
			}
		}
	}
	
	calculateTurnAroundTime(number, burst_time, wait_time, turn_around_time);
	
	displayProcessTable(number, processes, burst_time, priority, wait_time, turn_around_time);
	displayAvgTime(number, wait_time, turn_around_time);
}

void ps(int number, int processes[], int burst_time[], int priority[]) {
	int start_time[number], wait_time[number], turn_around_time[number];
	
	int i, j;
	for (i = 0; i < number - 1; i++) {
		for( j = i+ 1; j < number; j++) {
			if ((priority[j] > priority[i]) || (priority[j] == priority[i] && processes[j] < processes[i])) {
				swap(i,j, processes, burst_time, priority, arrival_time);
			}
		}
	}
	
	calculateWaitTime(number, burst_time, wait_time, start_time);
	calculateTurnAroundTime(number, burst_time, wait_time, turn_around_time);
	
	displayProcessTable(number, processes, burst_time, priority, wait_time, turn_around_time);
	displayAvgTime(number, wait_time, turn_around_time);	
}

void createProcessTable(int number, int processes[], int burst_time[], int priority[]) {
	int i;
	for(i = 0; i < number; i++) {
		printf("Enter Burst Time and Priority for Process %d :",i+1);
		scanf("%d",&burst_time[i]);
		scanf("%d",&priority[i]);
		processes[i]=i+1;
	}
}

int main() {
	int number, choice;
	printf("\nEnter number of processes: ");
	scanf("%d",&number);
	
	int processes[number], burst_time[number], priority[number];
	createProcessTable(number, processes, burst_time, priority);
	
	
	do {
		int i, temp_processes[number], temp_burst_time[number], temp_priority[number];
		for (i = 0; i < number; i++) {
			temp_processes[i] = processes[i];
			temp_burst_time[i] = burst_time[i];
			temp_priority[i] = priority[i];
		}
		
		printf("\n1. FCFS Scheduling \n2. SJF Scheduling \n3. RR Scheduling \n4. Priority Scheduling \n5. Exit");
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
		
		switch(choice) {
			case 1: fcfs(number, temp_processes, temp_burst_time, temp_priority);
					break;
			case 2: sjf(number, temp_processes, temp_burst_time, temp_priority);
					break;
			case 3: rr(number, temp_processes, temp_burst_time, temp_priority);
					break;
			case 4: ps(number, temp_processes, temp_burst_time, temp_priority);
					break;
			case 5: return 0;
			default: printf("\nPlease enter correct option !!!");
		}
	} while (choice != 5);
	
	return 0;
}
