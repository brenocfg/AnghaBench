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
typedef  int /*<<< orphan*/  u8 ;
struct stat {scalar_t__ st_size; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int MIN (int,scalar_t__) ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int _O_BINARY ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 int /*<<< orphan*/  ftruncate (int,scalar_t__) ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testMalloc (int) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int /*<<< orphan*/  write (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void copy_file(const char *zFrom, const char *zTo, int isDatabase){

  if( access(zFrom, F_OK) ){
    unlink(zTo);
  }else{
    int fd1;
    int fd2;
    off_t sz;
    off_t i;
    struct stat buf;
    u8 *aBuf;

    fd1 = open(zFrom, O_RDONLY | _O_BINARY, 0644);
    fd2 = open(zTo, O_RDWR | O_CREAT | _O_BINARY, 0644);

    fstat(fd1, &buf);
    sz = buf.st_size;
    ftruncate(fd2, sz);

    aBuf = testMalloc(4096);
    for(i=0; i<sz; i+=4096){
      int bLockPage = isDatabase && i == 0;
      int nByte = MIN((bLockPage ? 4066 : 4096), sz - i);
      memset(aBuf, 0, 4096);
      read(fd1, aBuf, nByte);
      write(fd2, aBuf, nByte);
      if( bLockPage ){
        lseek(fd1, 4096, SEEK_SET);
        lseek(fd2, 4096, SEEK_SET);
      }
    }
    testFree(aBuf);

    close(fd1);
    close(fd2);
  }
}