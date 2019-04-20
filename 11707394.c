#include<stdio.h>
#include<stdlib.h>
struct process
{
	int p_no,arrival_time,burst_time,waiting_time,turnaround_time,remain_burst;
	int finished;
}process[100];

int NoOfProcess;
int queue[100];
int front=-1,rear=-1;

void Push(int i)
{
	if(rear==100)
	{
			printf("OVERFLOW");
			exit(0);
	}
	rear++;
	queue[rear]=i;
	if(front==-1)
	{
		front=0;
	}
}

int Pop()   
{
	if(front==-1)
	{
		printf("UNDERFLOW");
		exit(0);
	}
	int temp=queue[front];
	if(front==rear)
	{
		front=rear=-1;
	}
	else
	{
		front++;
	}
	return temp;

}


int PresentInQueue(int i)
{
	int k;
	for(k=front;k<=rear;k++)
	{
		if(queue[k]==i)
		{
			return 1;
		}
	}
	return 0;
}


void SortProcess()
{
	struct process temp;
	int i,j;
	for(i=0;i<NoOfProcess-1;i++)
	{
		for(j=i+1;j<NoOfProcess;j++)
		{
			if(process[i].arrival_time>process[j].arrival_time)
			{
				temp=process[i];
				process[i]=process[j];
				process[j]=temp;
			}
		}
	}
}


int main()
{
	int i,j,c,time=0,total_burst_time=0,time_quantum,k;
	float avg_waiting_time=0,avg_turnaround_time=0;
	X:
 	printf("Enter no of processes present:");
 	scanf("%d",&NoOfProcess);
 	for(i=0,c=1;i<NoOfProcess;i++,c++)
 	{
 		process[i].p_no = c;
 		printf("\n\nEnter Arrival Time and Burst Time of Process %d:",process[i].p_no);
 		scanf("%d%d",&process[i].arrival_time,&process[i].burst_time);
 		process[i].remain_burst=process[i].burst_time;
 		process[i].finished=0;
 		total_burst_time +=process[i].burst_time;
	}
	if(NoOfProcess != 0)
	{
	printf("\nEnter The value of the Time Quantum:");
	scanf("%d",&time_quantum);
	SortProcess();
	Push(0);          
	printf("\nProcesses Sequence is: ");

	for(time=process[0].arrival_time;time < total_burst_time;) 
	{   
		i=Pop();
		if(process[i].remain_burst<=time_quantum)
		{   
			printf(" %d to %d -> process %d \t",time,time + process[i].remain_burst,process[i].p_no);
        	time+=process[i].remain_burst;
			process[i].remain_burst=0;
			process[i].finished=1;          
        	process[i].waiting_time=time-process[i].arrival_time-process[i].burst_time;
        	process[i].turnaround_time=time-process[i].arrival_time;       
        	for(j=0;j<NoOfProcess;j++)
        	{
            	if(process[j].arrival_time<=time && process[j].finished!=1&& PresentInQueue(j)!=1)
            	{
            		Push(j);
            	}
        	}
    	}
    	else
    	{
    		printf("%d to %d -> process %d \t",time,time + time_quantum,process[i].p_no);
    		time  +=  time_quantum;
    		process[i].remain_burst	 -=	 time_quantum;
    		for(j=0;j<NoOfProcess;j++)
        	{
            	if(process[j].arrival_time <= time && process[j].finished!=1  && i!=j && PresentInQueue(j)!=1)
            	{
            		Push(j);
            	}
        	}
        	Push(i);
    	}
	}
	printf("\n\nProcess\t     ArrivalTime\tBurstTime\tWaitingTime\tTurnAroundTime");
	for(i=0;i<NoOfProcess;i++)
	{
		avg_waiting_time		+=	process[i].waiting_time;
		avg_turnaround_time		+=	process[i].turnaround_time;
		printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",process[i].p_no,process[i].arrival_time,process[i].burst_time,process[i].waiting_time,process[i].turnaround_time);
	}
	printf("\nAverage waiting time of this scenario is :%.1f",avg_waiting_time/NoOfProcess);
	printf("\nAverage Turnaround time of this scenario is :%.1f",avg_turnaround_time/NoOfProcess);
	return 0;
	}
	else
	{
		printf("\t\t\t\t********Invalid Input******* \nIf you want to Give some value to NoOfProcesses again press '1' and if not press any other digit :");
		scanf("%d",&k);
		if(k == 1)
		{
			goto X;
		}
		else
		{
			exit(0);
		}
		
	}
}

