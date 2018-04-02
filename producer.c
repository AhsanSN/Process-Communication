#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <stdlib.h>
 
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    int mesg_text[10]; //queue size
} message; 
 
int main()
{
    FILE *fp; //file object
    key_t key;
    int msgid;
    int rand_num; //random number

    //create a producer txt file
    fp = fopen("producer.txt", "w+");

    srand(time(NULL));   // should only be called once

    // ftok to generate unique key
    key = ftok("progfile", 65);
 
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;

    for (int j = 0; j<100; j++)// 100 x 10 = 1000 numbers
    {
		for (int i = 0; i<10; i++) //queue of length 10
		{
		        //generate random numbers
			rand_num = rand() % 100;
			message.mesg_text[i] = rand_num; //save it in queue 
			fprintf(fp, "%d \n",message.mesg_text[i]);//save to file
		}

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);
    }
    
    //close file
    fclose(fp);
    
    return 0;
}
