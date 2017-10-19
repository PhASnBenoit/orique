#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int fin=0;

void deroute(int no) {
  switch(no) {
  case SIGCHLD:  // mort d'un fils
     printf("Un fils est mort !\n");
     wait(NULL);
  case SIGUSR1: 
     printf("PCTRL: Signal fin de travail machine reçu.\n");
  break;
  case SIGUSR2:
     fin = 1;
     printf("PCTRL: Signal de fin de fabrication reçu.\n");
  break;
  } // sw
} // deroute

int main () {
  int fk;
  int i;
  int pid[3];
  char chTmp[10];
  int tmp;

  signal(SIGCHLD, deroute);
  signal(SIGUSR1, deroute);
  signal(SIGUSR2, deroute);
  
  printf("PCTRL: Démarrage.\n"); 
  // creation des processus machine
  for(i=0 ; i<3 ; i++) {
    pid[i] = fork();
    switch(pid[i]) {
    case -1: // erreur
      printf("PCTRL: Erreur de cration d'un processus machine.\n"); 
      return -1;
    case 0: // fils
      printf("PM: Démarrage du processus machine %d.", pid[i]); 
      execl("./pm", "pm", 0);
      return -1;
    } // sw
  } // for  

  sleep(3);  // attente cration des proessus

  do {
    printf("PCTRL: Démarrage de la fabrication.\n"); 
    for(i=0 ; i<3 ; i++) { kill(pid[i], SIGUSR1); }

    printf("PCTRL: Attente de la fin de fabrication.\n"); 
    if (!fin) pause();
    if (!fin) pause();
    if (!fin) pause();
    if (!fin) { 
       printf("PCTRL: Fin du cycle de fabrication.\n"); 
       printf("PCTRL: Avance du tapis roulant.\n"); 
       sleep(3);
       printf("PCTRL: Fin avance du tapis. Ready pour une nouvelle fabrication.\n"); 
       sleep(2);
    } // if fin
  } while (!fin);

  printf("PCTRL: Arret des processus machine.\n");
  for(i=0 ; i<3 ; i++) { kill(pid[i], SIGKILL); }

  printf("PCTRL: Fin du programme.\n");


} // main

