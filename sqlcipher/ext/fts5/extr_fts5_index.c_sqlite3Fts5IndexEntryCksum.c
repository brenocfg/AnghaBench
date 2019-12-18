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
typedef  int u64 ;
typedef  int i64 ;

/* Variables and functions */
 scalar_t__ FTS5_MAIN_PREFIX ; 

u64 sqlite3Fts5IndexEntryCksum(
  i64 iRowid, 
  int iCol, 
  int iPos, 
  int iIdx,
  const char *pTerm,
  int nTerm
){
  int i;
  u64 ret = iRowid;
  ret += (ret<<3) + iCol;
  ret += (ret<<3) + iPos;
  if( iIdx>=0 ) ret += (ret<<3) + (FTS5_MAIN_PREFIX + iIdx);
  for(i=0; i<nTerm; i++) ret += (ret<<3) + pTerm[i];
  return ret;
}