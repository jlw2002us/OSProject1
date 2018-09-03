//Jennifer Wasson
//Operating Systems
//Project 1
//Source used:
//https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html





#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void helpoptions()
{
  printf("options for running Project 1:  \n");
  printf("type ./proj1 -h for help options\n");
  printf("type ./proj1 -p to generate test perror message.\n");
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
        if (optopt == 'n')
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
                   
 
  

  if(hflag == 1)
  {
     helpoptions();
     return 1;
  }
   //change the number user entered into int
   if(xvalue != NULL){

     n = atoi(xvalue);
     if (n == 0){
       printf("Error:  non-numerical data entered\n");
       return 1;}
  }
   //make the error string for perror
   char str1[50];
   char str2[13];
   //check user input for executable
   if(strlen(argv[0]) > 20){
     printf("%s","Executable name too long");
     return 1;
   }
   strcpy(str1, argv[0]);
   strcpy(str2, " : Error: ");
   if(strlen(str2)  < 14)
      strcat(str1,str2);
   
  if(pflag == 1)
  { 

   printf("Testing perror with fopen:  \n");
    
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
   //sleep(10);
   
   //int nchars  = atoi(argv[3]);
   //char mybuf[100];
   //char ch;
   //for (i = 0; i < nchars; i++){
    //scanf(" %c", &ch);
    //mybuf[i] = ch;
    //}
  // mybuf[i] = '\0';
   
//   fprintf(stderr, "process ID: %ld %s\n", (long)getpid(), mybuf);
   fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",
      i, (long)getpid(), (long)getppid(), (long)childpid);
   //sleep(m);
  return 0;
}
