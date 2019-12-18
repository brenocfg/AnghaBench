#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
typedef  scalar_t__ off_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ DemoFile ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int SQLITE_IOERR_WRITE ; 
 int SQLITE_OK ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t write (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static int demoDirectWrite(
  DemoFile *p,                    /* File handle */
  const void *zBuf,               /* Buffer containing data to write */
  int iAmt,                       /* Size of data to write in bytes */
  sqlite_int64 iOfst              /* File offset to write to */
){
  off_t ofst;                     /* Return value from lseek() */
  size_t nWrite;                  /* Return value from write() */

  ofst = lseek(p->fd, iOfst, SEEK_SET);
  if( ofst!=iOfst ){
    return SQLITE_IOERR_WRITE;
  }

  nWrite = write(p->fd, zBuf, iAmt);
  if( nWrite!=iAmt ){
    return SQLITE_IOERR_WRITE;
  }

  return SQLITE_OK;
}