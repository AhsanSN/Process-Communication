// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    int mesg_text[10];//queue size
} message;
 
int main()
{
    FILE *fp; //file object
    key_t key;
    int msgid;

    //create a consumer txt file
    fp = fopen("consumer.txt", "w+");
 
    // ftok to generate unique key
    key = ftok("progfile", 65);
 
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
 
    for (int j = 0; j<100; j++)// repeat 100 times. 100 x 10 = 1000 numbers
    {
		// msgrcv to receive message
		msgrcv(msgid, &message, sizeof(message), 1, 0);
		for (int i = 0; i<10; i++)
		{
			fprintf(fp, "%d \n",message.mesg_text[i]);//write to file
		}
    }
    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    //close file
    fclose(fp);
 
    return 0;
}
