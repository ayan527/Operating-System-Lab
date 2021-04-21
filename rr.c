#include<stdio.h>
#include<conio.h>
#include<stdbool.h>

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

void calculateTurnAroundTime(int number, int arrival_time[], int turn_around_time[]) {
	int i;
	for(i = 0; i < number; i++) {
		turn_around_time[i] = turn_around_time[i] - arrival_time[i];
	}
}

void calculateWaitTimeRr(int number, int wait_time[], int turn_around_time[], int burst_time[]) {
	int i;
	for(i = 0; i < number; i++) {
		wait_time[i] = turn_around_time[i] - burst_time[i];
	}
}

void queueUpdation(int ready_queue[], int timer, int number, int maxProccessIndex) {
	int zeroIndex, i;
	for(i = 0; i < number; i++) {
		if(ready_queue[i] == 0){
			zeroIndex = i;
			break;
		}
	}
	ready_queue[zeroIndex] = maxProccessIndex + 1;
}

void queueMaintainence(int ready_queue[], int number) {
	int i, temp;
	for(i = 0; (i < number-1) && (ready_queue[i+1] != 0) ; i++) {
		temp = ready_queue[i];
		ready_queue[i] = ready_queue[i+1];
		ready_queue[i+1] = temp;
	}
}

void checkNewArrival(int timer, int arrival_time[], int number, int maxProccessIndex, int ready_queue[]){
	if(timer <= arrival_time[number-1]) {
	bool newArrival = false;
	int j;
	for(j = (maxProccessIndex+1); j < number; j++){
			if(arrival_time[j] <= timer){
			if(maxProccessIndex < j){
				maxProccessIndex = j;
				newArrival = true;
			}
		}
	}
	
	if(newArrival)
		queueUpdation(ready_queue,timer,number, maxProccessIndex);
	}
}

void calculateTimeRr(int number, int burst_time[], int arrival_time[], int turn_around_time[], int wait_time[], int time_quantum) {
	int timer = 0;
	int maxProcessIndex = 0;
	int ready_queue[number], temp_burst_time[number];
	bool complete_process[number];
	
	int i;
	for(i = 0; i < number; i++) {
		temp_burst_time[i] = burst_time[i];
		ready_queue[i] = 0;
		complete_process[i] = false;
	}
	
	while(timer < arrival_time[0])
		timer++;
	ready_queue[0] = 1;
	
	while(true) {
		bool flag = true;
		for(i = 0; i < number; i++){
			if(temp_burst_time[i] != 0){
				flag = false;
				break;
			}
		}
		if(flag)
			break;

		for(i = 0; (i < number) && (ready_queue[i] != 0); i++) {
			int counter = 0;
			while((counter < time_quantum) && (temp_burst_time[ready_queue[0]-1] > 0)) {
				temp_burst_time[ready_queue[0]-1] -= 1;
				timer += 1;
				counter++;

				checkNewArrival(timer, arrival_time, number, maxProcessIndex, ready_queue);
			}
			
			if((temp_burst_time[ready_queue[0]-1] == 0) && (complete_process[ready_queue[0]-1] == false)) {
				turn_around_time[ready_queue[0]-1] = timer;	
				complete_process[ready_queue[0]-1] = true;
			}
			
			bool idle = true;
			if(ready_queue[number-1] == 0) {
				int j;
				for(j = 0; j < number && ready_queue[j] != 0; j++){
					if(complete_process[ready_queue[j]-1] == false){
						idle = false;
					}
				}
			}
			else
				idle = false;

			if(idle) {
				timer++;
				checkNewArrival(timer, arrival_time, number, maxProcessIndex, ready_queue);
			}
	
			queueMaintainence(ready_queue,number);
		}
	}
	
	calculateTurnAroundTime(number, arrival_time, turn_around_time);
	calculateWaitTimeRr(number, wait_time, turn_around_time, burst_time);
}

void swap(int i, int j, int processes[], int burst_time[], int priority[], int arrival_time[]) {
	processes[j]=processes[j]+processes[i]-(processes[i]=processes[j]);
	priority[j]=priority[j]+priority[i]-(priority[i]=priority[j]);
	burst_time[j]=burst_time[j]+burst_time[i]-(burst_time[i]=burst_time[j]);
	arrival_time[j]=arrival_time[j]+arrival_time[i]-(arrival_time[i]=arrival_time[j]);
}

void rr(int number, int processes[], int burst_time[], int priority[], int arrival_time[]) {
	int time_quantum, turn_around_time[number], wait_time[number];
	
	printf("\nEnter time quantum: ");
	scanf("%d",&time_quantum);
	
	int i, j;
	for (i = 0; i < number - 1; i++) {
		for( j = i+ 1; j < number; j++) {
			if (arrival_time[j] < arrival_time[i]) {
				swap(i, j, processes, burst_time, priority, arrival_time);
			}
		}
	}
	
	calculateTimeRr(number, burst_time, arrival_time, turn_around_time, wait_time, time_quantum);
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
	
	rr(number, processes, burst_time, priority, arrival_time);
	
	return 0;
}
