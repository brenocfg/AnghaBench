#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ i64 ;
struct TYPE_4__ {int szPage; } ;
struct TYPE_5__ {int /*<<< orphan*/  pWalFd; TYPE_1__ hdr; } ;
typedef  TYPE_2__ Wal ;

/* Variables and functions */
 scalar_t__ WAL_FRAME_HDRSIZE ; 
 int sqlite3OsRead (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  testcase (int) ; 
 scalar_t__ walFrameOffset (int /*<<< orphan*/ ,int) ; 

int sqlite3WalReadFrame(
  Wal *pWal,                      /* WAL handle */
  u32 iRead,                      /* Frame to read */
  int nOut,                       /* Size of buffer pOut in bytes */
  u8 *pOut                        /* Buffer to write page data to */
){
  int sz;
  i64 iOffset;
  sz = pWal->hdr.szPage;
  sz = (sz&0xfe00) + ((sz&0x0001)<<16);
  testcase( sz<=32768 );
  testcase( sz>=65536 );
  iOffset = walFrameOffset(iRead, sz) + WAL_FRAME_HDRSIZE;
  /* testcase( IS_BIG_INT(iOffset) ); // requires a 4GiB WAL */
  return sqlite3OsRead(pWal->pWalFd, pOut, (nOut>sz ? sz : nOut), iOffset);
}