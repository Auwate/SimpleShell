#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define STRING_LENGTH 255
#define DELIMINATORS " \t\n"

int tokenizeString (char * line, char * deliminators, char ** tokenizedString[]);
void findCommand (char ** command, int amountOfWords);
void errorChecker ();

int main (void) {

  // String variable declaration
  // and initilization
  char * userCommand = (char *)malloc(sizeof(char)*STRING_LENGTH);
  char ** tokenizedString[STRING_LENGTH];
  *(tokenizedString) = (char **) malloc (sizeof(char *) * STRING_LENGTH);

  // Shell interface
  while (1) {
    // Prompter
    fflush(stdout);
    fprintf(stdout,"myshell> ");
    fflush(stdout);
    // Get user input
    if (fgets(userCommand, STRING_LENGTH ,stdin) == NULL) {
      fprintf(stderr, "ERROR READING INPUT\n");
    }
    if (strcmp(userCommand, "\n") == 0) {
      continue;
    }
    // Tokenize
    int amountOfWords = tokenizeString(userCommand, DELIMINATORS, tokenizedString);
    findCommand(*tokenizedString, amountOfWords);
    
  }

}

/*
Logic: errorChecker() takes no parameter, as it uses the errno from the errno.h header. Using this, we check for errors, and quit when appropriate.
*/
void errorChecker () {

  if (errno == 0) {
    errno = 0;
    return;
  }

  if (errno == 3) {
    fprintf(stdout, "myshell: an error occurred: No such process\n");
    errno = 0;
    return;
  }

  else {

    printf("myshell: an error occurred: %s\n", strerror(errno));
    exit(1);

  }
  
}

/*
Parameters:
char * command: First word in the char ** tokenizedString[] array. In other words, it is the command the user wants to execute
Logic: Using strcmp(...), this method will find the command the user wanted to execute, and will print "unknown command" if it cannot find it.
*/
void findCommand (char * command[], int amountOfWords) {

  if (strcmp(command[0], "wait") == 0) {
    int * status = (int *) malloc (sizeof(int));
    
    pid_t processID = wait(status);

    if (processID == -1) {
      
      if (errno == 10) {
        fprintf(stdout, "myshell: no processes left\n");
      }
      else {
        fprintf(stdout, "myshell: process %d exited abnormally with signal %d: %s\n", processID, *status, strerror(errno));
      }
      
    }

    else {

      fprintf(stdout, "myshell: process %d exited normally with status %d\n", processID, *status);
      
    }

    return;
    
  }

  else if (strcmp(command[0], "exit") == 0 || strcmp(command[0], "quit") == 0) {
    
    exit(1);
    
  }

  else if (strcmp(command[0], "start" ) == 0 && amountOfWords > 1) {

    pid_t process = fork();

    if (process == 0) {
      execvp(command[1], (command)+1);
      // If it reaches after this, an error occurred
      errorChecker();
    }
    else if (process > 0) {
      fprintf(stdout, "myshell: process %d started\n", process);
      return;
    }
    else {
      errorChecker();
    }
    
  }

  else if (strcmp(command[0], "kill") == 0 && amountOfWords > 1) {

    int errorOccurred = kill(atoi(command[1]), SIGKILL);

    if (errorOccurred == -1) {
      errorChecker();
    }

    else {
      printf("myshell: process %s killed\n", command[1]);
    }
    
  }

  else if (strcmp(command[0], "stop") == 0 && amountOfWords > 1) {

    int errorOccurred = kill (atoi(command[1]), SIGSTOP);

    if (errorOccurred == -1) {
      errorChecker();
    }

    else {
      printf("myshell: process %s stopped\n", command[1]);
    }
    
  }

  else if (strcmp(command[0], "continue") == 0 && amountOfWords > 1) {

    int errorOccurred = kill (atoi(command[1]), SIGCONT);

    if (errorOccurred == -1) {
      errorChecker();
    }

    else {
      printf("myshell: process %s continued\n", command[1]);
    }
      
  }

  else if (strcmp(command[0], "run") == 0 && amountOfWords > 1) {

    int * status = (int *) malloc (sizeof(int));
    pid_t process = fork();

    if (process == 0) {
      execvp(command[1], (command)+1);
    }

    pid_t processID = waitpid(process, status, WUNTRACED);

    if (processID == -1) {
      fprintf(stdout, "myshell: process %d exited abnormally with signal %d: %s\n", processID, *status, strerror(errno));
    }

    else {
      fprintf(stdout, "myshell: process %d exited normally with status %d\n", processID, *status);
    }
    
  }

  else {
    
    printf("myshell: unknown command: %s\n", command[0]);
    
  }
  
}

/*
  Parameters:
  char * line: String to be tokenized
  char * deliminators: characters that will deliminate our string. Can be edited at the top @ DELIMINATORS.
  char ** tokenizedString[]: A pointer to a list of strings. The reason why it's a pointer is to edit the memory here in the method and to then read it back in main.
  Logic: Takes a string and splits it into its constitutent parts using the deliminators given.
*/
int tokenizeString (char * line, char * deliminators, char ** tokenizedString[]) {

  char * token = strtok(line, DELIMINATORS);

  int i = 0;

  while (token != NULL) {
    (*tokenizedString)[i++] = token;
    token = strtok(0, DELIMINATORS);
  }

  return i;
  
}
