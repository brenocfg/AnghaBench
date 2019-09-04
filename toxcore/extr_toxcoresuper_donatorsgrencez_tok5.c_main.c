#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xpd ;
typedef  int /*<<< orphan*/  xid ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  pipe (int*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int rand () ; 
 int read (int,int*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write (int,int*,int) ; 

int main(int i, char** msg)
{
  int j, fd[4], xpd, xid;
  if (--i<1)  return 1;
  srand(getpid());
  pipe(fd);
  while (xid=rand()%5, --i>0) {
    pipe(&fd[2]);
    j = (0==fork() ? 0 : 1);
    close(fd[j]);
    fd[j] = fd[j+2];
    close(fd[3-j]);
    if (j==0)  break;
  }
#define SendSc()  write(fd[1], &xid, sizeof(xid))
#define RecvPd()  read(fd[0], &xpd, sizeof(xpd))
#define A(g,v)  if (g) {xid=v; puts(msg[i+1]); fflush(stdout); SendSc();}
  SendSc();
  while (RecvPd(), 1) {
    sleep(1);
    if (i==0) {
      A( xpd==0 && xid==0 , 1 );
      A( xpd==1 && xid<=1 , 2 );
      A( xpd> 1 && xid> 1 , 0 );
      continue;
    }
    A( xpd==0 && xid> 1 , xid/4 );
    A( xpd==1 && xid!=1 , 1     );
    A( xpd==2 && xid<=1 , 2+xid );
    A( xpd>=3 && xid<=1 , 4     );
  }
  return 0;
}