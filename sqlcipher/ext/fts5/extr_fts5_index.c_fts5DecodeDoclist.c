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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  Fts5Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int,int) ; 
 scalar_t__ fts5DecodePoslist (int*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ fts5GetPoslistSize (int /*<<< orphan*/  const*,int*,int*) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferAppendPrintf (int*,int /*<<< orphan*/ *,char*,int,...) ; 
 int sqlite3Fts5GetVarint (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5DecodeDoclist(int *pRc, Fts5Buffer *pBuf, const u8 *a, int n){
  i64 iDocid = 0;
  int iOff = 0;

  if( n>0 ){
    iOff = sqlite3Fts5GetVarint(a, (u64*)&iDocid);
    sqlite3Fts5BufferAppendPrintf(pRc, pBuf, " id=%lld", iDocid);
  }
  while( iOff<n ){
    int nPos;
    int bDel;
    iOff += fts5GetPoslistSize(&a[iOff], &nPos, &bDel);
    sqlite3Fts5BufferAppendPrintf(pRc, pBuf, " nPos=%d%s", nPos, bDel?"*":"");
    iOff += fts5DecodePoslist(pRc, pBuf, &a[iOff], MIN(n-iOff, nPos));
    if( iOff<n ){
      i64 iDelta;
      iOff += sqlite3Fts5GetVarint(&a[iOff], (u64*)&iDelta);
      iDocid += iDelta;
      sqlite3Fts5BufferAppendPrintf(pRc, pBuf, " id=%lld", iDocid);
    }
  }

  return iOff;
}