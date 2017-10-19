#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

void deroute(int no) {
  switch(no) {
    case SIGUSR1:
    break;
  } // sw
} // deroute

int main (int argc, char *argv[]) {
  int pid;
  int tmp;

  signal(SIGUSR1, deroute);
  srand(time(NULL));
  pid = getpid();
  tmp = pid - getppid() + 4; 

  while (1) {
     printf("PM%d: Attente départ fabrication.\n", pid);
     pause();  // attente signal départ
   
     printf("PM%d: Fabrication en cours pour une durée de %d s.\n", pid, tmp);
     sleep(tmp);
     printf("PM%d: Fin de la Fabrication.\n", pid);
     kill (getppid(), SIGUSR1);
  } // wh
} // main

