#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  int pid = fork();
  if(pid > 0){
    write(p[1],0,1);
    wait((int *) 0);
    printf("%d: received pong\n",getpid());
  } else if (pid == 0){
    char byte[1];
    read(p[0],byte,1);
    write(p[1],byte,1);
    printf("%d: received ping\n",getpid());
  } else {
    return -1;
  }
  return 0;
}