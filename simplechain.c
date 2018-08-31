#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void helpoptions()
{
  printf("options for running Project 1:  \n");
  printf("type ./proj1 -h for help options\n");
  printf("type ./proj1 -p to enable perror messages.\n");
  printf("type ./proj1 -n x to run fork loop for x number of times.\n");
}
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

   while ((c = getopt (argc, argv, "hpn:")) != -1){
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
 }

  printf ("hflag = %d, pflag = %d, xvalue = %s\n",
          hflag, pflag, xvalue);

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
                   
 // if(xvalue != NULL){

   //n = atoi(xvalue);
  //}
  

  if(hflag == 1)
  {
     helpoptions();
     return 1;
  }
   //change the number user entered into int
   if(xvalue != NULL){

     n = atoi(xvalue);
  }
   //make the error string for perror
   char str1[50];
   char str2[13];
   strcpy(str1, argv[0]);
   strcpy(str2, " : Error: ");
   if(strlen(str2)  < 14)
      strcat(str1,str2);
   
  if(pflag == 1)
  { 

    
   FILE *fp;  
   fp = fopen("file.txt", "r");
   if( fp == NULL ) {
      perror(str1);
      return(-1);
   }
   fclose(fp);
   
  }
  

  
  for (i=1; i < n; i++)
  {
    childpid = fork();
    if (childpid == -1)
    {
       
       perror(str1);       
       return 1;
     }
     if(childpid)
       break;
   }
   
   fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
       i, (long)getpid(), (long)getppid(), (long)childpid);
  return 0;
}
