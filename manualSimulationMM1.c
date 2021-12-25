#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 10
typedef struct
{
    int start;
    int end;
}serv;
typedef struct
{
    int arrival_time;
    serv service ;
    int waiting_time;
    int system_time;
    
}cust;
int INTER_ARRIVAL_TIME[N]={0,10,60,60,120,10,60,120,10,120};
int SERVICE_TIME[N]={25,50,37,45,50,62,43,48,52,38};

int arrival_generator(int i)
{
    return INTER_ARRIVAL_TIME[i];
}
int service_generator(int i)
{
    return SERVICE_TIME[i];
}
int main()
{
    cust customer[N];
    int total_inter_arrival_time=0;
    int total_service_time=0;
    int total_waiting_time=0;
    int people_waiting=0;//number of customers who wait
    int total_system_time=0;
    int server_idle_time=0;
    int i=0;
    while(i<N)
    {
        if(i==0)
        {
            customer[0].arrival_time=0;
            customer[0].service.start=0;
        }
        else
        {
            customer[i].arrival_time=customer[i-1].arrival_time+arrival_generator(i);
            if(customer[i].arrival_time<=customer[i-1].service.end)
            {
                customer[i].service.start=customer[i-1].service.end;
            }
            else
            {
                customer[i].service.start=customer[i].arrival_time;
                server_idle_time=server_idle_time+(customer[i].arrival_time-customer[i-1].service.end);
            }
        }
        customer[i].waiting_time=customer[i].service.start-customer[i].arrival_time;
        if(customer[i].waiting_time!=0)
        {
            people_waiting=people_waiting+1;
        }
        total_waiting_time=total_waiting_time+customer[i].waiting_time;
        customer[i].service.end=customer[i].service.start+service_generator(i);    
        customer[i].system_time=customer[i].waiting_time+(customer[i].service.end-customer[i].service.start);
        total_system_time=total_system_time+customer[i].system_time;
        total_inter_arrival_time=total_inter_arrival_time+arrival_generator(i);
        total_service_time=total_service_time+(customer[i].service.end-customer[i].service.start);
        i++;
    }
    for(int j=0;j<N;j++)
    {
        printf("===========================================================================================================\n");
        printf("Customer %d\n",j+1);
        printf("Arrival time=%d\n",customer[j].arrival_time);
        printf("Time service begins=%d\n",customer[j].service.start);
        printf("Time service ends=%d\n",customer[j].service.end);
        printf("Service time=%d\n",customer[j].service.end-customer[j].service.start);
        printf("Waiting time=%d\n",customer[j].waiting_time);
        printf("System time=%d\n",customer[j].system_time);
    }
    printf("**************************************************************************************************\n");
    printf("Mean inter arrival time=%.2lf\n",(double)total_inter_arrival_time/((double)N-1));
    printf("Mean service time=%.2lf\n",(double)total_service_time/(double)N);
    printf("Mean waiting time=%.2lf\n",(double)total_waiting_time/(double)N);
    printf("Mean waiting time for those who wait=%.2lf\n",(double)total_waiting_time/people_waiting);
    printf("Mean time in the system=%.2lf\n",(double)total_system_time/(double)N);
    printf("The probability that the system is idle=%.2lf\n",(double)server_idle_time/(double)customer[N-1].service.end);
    return 0;
}












