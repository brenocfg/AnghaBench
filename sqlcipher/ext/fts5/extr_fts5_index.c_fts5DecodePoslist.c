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
typedef  int /*<<< orphan*/  Fts5Buffer ;

/* Variables and functions */
 scalar_t__ fts5GetVarint32 (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferAppendPrintf (int*,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int fts5DecodePoslist(int *pRc, Fts5Buffer *pBuf, const u8 *a, int n){
  int iOff = 0;
  while( iOff<n ){
    int iVal;
    iOff += fts5GetVarint32(&a[iOff], iVal);
    sqlite3Fts5BufferAppendPrintf(pRc, pBuf, " %d", iVal);
  }
  return iOff;
}