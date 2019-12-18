#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  aBuf ;
struct TYPE_6__ {scalar_t__ rc; } ;
typedef  TYPE_1__ Error ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ filesize_x (TYPE_1__*,char const*) ; 
 int open (char const*,int,...) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,char const*) ; 
 int /*<<< orphan*/  system_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_error_x (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void filecopy_x(
  Error *pErr,
  const char *zFrom,
  const char *zTo
){
  if( pErr->rc==SQLITE_OK ){
    i64 nByte = filesize_x(pErr, zFrom);
    if( nByte<0 ){
      test_error_x(pErr, sqlite3_mprintf("no such file: %s", zFrom));
    }else{
      i64 iOff;
      char aBuf[1024];
      int fd1;
      int fd2;
      unlink(zTo);

      fd1 = open(zFrom, O_RDONLY);
      if( fd1<0 ){
        system_error(pErr, errno);
        return;
      }
      fd2 = open(zTo, O_RDWR|O_CREAT|O_EXCL, 0644);
      if( fd2<0 ){
        system_error(pErr, errno);
        close(fd1);
        return;
      }

      iOff = 0;
      while( iOff<nByte ){
        int nCopy = sizeof(aBuf);
        if( nCopy+iOff>nByte ){
          nCopy = nByte - iOff;
        }
        if( nCopy!=read(fd1, aBuf, nCopy) ){
          system_error(pErr, errno);
          break;
        }
        if( nCopy!=write(fd2, aBuf, nCopy) ){
          system_error(pErr, errno);
          break;
        }
        iOff += nCopy;
      }

      close(fd1);
      close(fd2);
    }
  }
}