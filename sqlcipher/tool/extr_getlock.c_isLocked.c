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
struct flock {int l_type; unsigned int l_start; unsigned int l_len; scalar_t__ l_pid; int /*<<< orphan*/  l_whence; } ;
typedef  int /*<<< orphan*/  lk ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETLK ; 
 int F_UNLCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  memset (struct flock*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int isLocked(
  int h,                /* File descriptor to check */
  int type,             /* F_RDLCK or F_WRLCK */
  unsigned int iOfst,   /* First byte of the lock */
  unsigned int iCnt,    /* Number of bytes in the lock range */
  const char *zType     /* Type of lock */
){
  struct flock lk;

  memset(&lk, 0, sizeof(lk));
  lk.l_type = type;
  lk.l_whence = SEEK_SET;
  lk.l_start = iOfst;
  lk.l_len = iCnt;
  if( fcntl(h, F_GETLK, &lk)==(-1) ){
    fprintf(stderr, "fcntl(%d) failed: errno=%d\n", h, errno);
    exit(1);
  }
  if( lk.l_type==F_UNLCK ) return 0;
  printf("%s lock held by %d\n", zType, (int)lk.l_pid);
  return 1;
}