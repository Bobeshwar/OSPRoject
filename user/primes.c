#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  for (int i = 2;i <=35; i = i+1){
    write(p[1], &i, sizeof(i));
  }
  close(p[1]);
  int prime[1];
  int oldPipe[2];
  memcpy(oldPipe,p,sizeof(p));

  int pid = 0;
  int result = 0;
  while (!pid){
    int check = read(oldPipe[0], prime, sizeof(prime));
    if(check){
        int newPipe[2];
        pipe(newPipe);
        pid = fork();
        if (pid == 0){
          
            memcpy(oldPipe,newPipe, sizeof(newPipe));
            close(oldPipe[1]);
        } else {
            result = prime[0];
            int num = prime[0];
            while (read(oldPipe[0], prime, sizeof(prime))){
                if(prime[0]%num){
                    write(newPipe[1],prime,sizeof(prime[0]));
                }
            }
            close(newPipe[1]);
            close(oldPipe[0]);
        }
    } else {
      close(oldPipe[0]);
      exit(0);
    }
  }
  wait((int*)0);
  if (result){
    printf("prime %d\n",result);
  }
  return 0;
}