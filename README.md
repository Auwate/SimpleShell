# SimpleShell
C program that mimics a Unix Bash shell, which would take in a set list of commands.

Commands:

**start** [[command]]
  Creates a new process with the command
  Example: start ls -- Creates a new process that runs the ls command
  
**stop** [[processID]]
  Pauses a process using their ID
  Example: stop 190 -- Stops the process with the ID 190
  
**kill** [[processID]]
  Terminates a process using their ID
  Example: kill 240 -- Kills the process with the ID 240
  
**continue** [[processID]]
  Resumes a process that was stopped using their ID
  Example: continue 1241 -- Continues the process with the ID 1241
  
**run** [[command]]
  Creates a new process with the command, but also causes the main process to block until the new process is done
  Example: run ls -- Creates a new process that runs the ls command and the main function will not progress until the ls command has finished.

**<** [[file name]]
  Runs the script given by file name
  Example: < myscript -- Runs any commands inside of myscript.
  
**exit**
  Exits the program
  Example: exit
  
**quit**
  Exits the program
  Example: quit
  
**wait**
  Waits for any process to finish
  Example: wait -- Waits until any process has finished. If there are no processes, myshell will notify the user.

Makefile

**make**
  Runs the makefile
