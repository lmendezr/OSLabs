/* Sample program to handle system signals */

#include <signal.h>
#include <stdio.h>


void * siginthandler(int myint)
{
   printf("\nSIGINT Signal Handled!!\n\n");
   exit(0);
}

void * sigtermhandler(int myint)
{
   printf("\nSIGTERM Signal Handled!!\n\n");
   exit(0);
}

int main()
{
   signal( SIGINT, (void *)  siginthandler );
   signal( SIGTERM, (void *)  sigtermhandler );

   while(1) {
	printf("Doing Nothing...\n");
	sleep(1);
   }
}
