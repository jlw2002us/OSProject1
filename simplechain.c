#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  pid_t childpid = 0;
  int i, n;
    int hflag = 0;
  int pflag = 0;
     char *xvalue = NULL;
  int index;
  int c;

  opterr = 0;

  if (argc <= 1)
  {
    fprintf(stderr, "Usage: %s process\n", argv[0]);
    return 1;
  }
   
 
  while ((c = getopt (argc, argv, "hpn:")) != -1)
    switch (c)
      {
      case 'h':
        hflag = 1;
        break;
    case 'p':
        pflag = 1;
        break;
      case 'n':
        xvalue = optarg;
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
  if(xvalue != NULL)
   n = atoi(xvalue);
   //printf ("hflag = %d, pflag = %d, xvalue = %s\n",
   //hflag, pflag, xvalue);

  for (i=1; i < n; i++)
  {
     childpid = fork();
     if (childpid == -1)
     {
        perror("Failed to fork");
        return 1;
     }
     if(childpid)
       break;
   }
   fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
         i, (long)getpid(), (long)getppid(), (long)childpid);
  return 0;
}
