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
typedef  int u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int* aFts5UnicodeBlock ; 
 int* aFts5UnicodeData ; 
 scalar_t__* aFts5UnicodeMap ; 
 int /*<<< orphan*/  assert (int) ; 

int sqlite3Fts5UnicodeCategory(u32 iCode) { 
  int iRes = -1;
  int iHi;
  int iLo;
  int ret;
  u16 iKey;

  if( iCode>=(1<<20) ){
    return 0;
  }
  iLo = aFts5UnicodeBlock[(iCode>>16)];
  iHi = aFts5UnicodeBlock[1+(iCode>>16)];
  iKey = (iCode & 0xFFFF);
  while( iHi>iLo ){
    int iTest = (iHi + iLo) / 2;
    assert( iTest>=iLo && iTest<iHi );
    if( iKey>=aFts5UnicodeMap[iTest] ){
      iRes = iTest;
      iLo = iTest+1;
    }else{
      iHi = iTest;
    }
  }

  if( iRes<0 ) return 0;
  if( iKey>=(aFts5UnicodeMap[iRes]+(aFts5UnicodeData[iRes]>>5)) ) return 0;
  ret = aFts5UnicodeData[iRes] & 0x1F;
  if( ret!=30 ) return ret;
  return ((iKey - aFts5UnicodeMap[iRes]) & 0x01) ? 5 : 9;
}