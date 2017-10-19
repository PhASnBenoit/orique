#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

void deroute(int no) {
  switch(no) {
  case SIGCHLD:  // mort d'un fils
     printf("Un fils est mort !\n");
     wait(NULL);
  case SIGTERM: 
     printf("Vous pouvez pas utiliser SIGTERM\n");
  break;
  case SIGINT:
     printf("Vous pouvez pas utiliser SIGINT\n");
  break;
  } // sw
} // deroute

int main () {
  int fk;
  signal(SIGCHLD, deroute);
  signal(SIGTERM, deroute);
  signal(SIGINT, deroute);
  fk = fork();

  switch(fk) {
  case 0: // fils
     printf("Je suis le fils et je meurs de suite\n");
     return 0;
  } // sw
  while (1)
     pause();
} // main

