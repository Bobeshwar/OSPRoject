#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc != 2){
    char *error = "Sleep needs 1 arguments";
    write(1,error,strlen(error));
    exit(1);
  } else {
    sleep(atoi(argv[1]));
    exit(0);
  }
}