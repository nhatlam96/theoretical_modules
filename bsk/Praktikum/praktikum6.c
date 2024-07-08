/*
 *  Beispielprogramm fuer signal und exec. WiSe 2020 
 *  Autor: A. Brunner und D. Bub
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
#include <time.h>
#include <signal.h>


void sig_handler1 (int);
void sig_handler2 (int);

int counter=0;

int
main ()
{
  time_t rawtime;
  struct tm *timeinfo;

  printf ("[PID: %d, PPID: %d] Hallo! Dieses Programm soll dazu dienen, "
	  "die Verwendung von Signalen und der Systemroutine execvp() besser"
	  "zu verstehen\n", getpid (), getppid ());

  // Einrichten des SIGUSR1-Signal-Handlers
  signal (SIGUSR1, &sig_handler1);

  // Endlosschleife, bis SIGUSR2-Signal empfangen
  while (counter<5)
    {
      time (&rawtime);
      timeinfo = localtime (&rawtime);
      printf ("[PID: %d, PPID: %d] Die aktuelle Systemzeit betraegt: %s\n",
	      getpid (), getppid (), asctime (timeinfo));
      sleep (1);
    }

  return 0;
}


void
sig_handler1 (int i /* nicht benutzt */ )
{
  printf ("[PID: %d, PPID: %d] SIGUSR1-Signal empfangen. SigNr: %d\n", getpid (),
	  getppid (), i);
	  fflush(stdout);
	  counter++;
  // Ignoriere weitere SIGUSR1-Signale
  signal (SIGUSR1, SIG_IGN);

  // Einrichten des SIGUSR1-Signal-Handlers
  //signal (SIGHUP, &sig_handler2);
  return;
}


void
sig_handler2 (int i /* nicht benutzt */ )
{
  printf ("[PID: %d, PPID: %d] SIGHUP-Signal empfangen.\n", getpid (),
	  getppid ());
  int pid, ret;

  if ((pid = fork ()) < 0)
    {
      perror ("fork error");
      exit (1);
    }

  if ((pid = fork ()) == 0)
    {
      /* Parameterliste für xeyes vorbereiten */
      char *args[] =
	{ "xeyes", "+shape", "-fg", "blue", "-bg", "green", (char *) NULL };

      /* Programm starten */
      ret = execvp ("xeyes", args);

      /* execvp-Fehlerbehandlung */
      if (ret == -1)
	{
	  int saved_errno = errno;
	  error (0, saved_errno, "exec fehlgeschalgen: %d", saved_errno);
	}

      /* Wann wird dieser Text ausgegeben? */
      printf ("[PID: %d, PPID: %d] Nach dem exec...\n", getpid (),
	      getppid ());
    }
  else
    {
      // Beende den Elternprozess
      exit (0);
    }


  return;
}