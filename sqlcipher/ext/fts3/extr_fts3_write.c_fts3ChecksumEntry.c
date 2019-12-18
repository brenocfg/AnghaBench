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
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */

__attribute__((used)) static u64 fts3ChecksumEntry(
  const char *zTerm,              /* Pointer to buffer containing term */
  int nTerm,                      /* Size of zTerm in bytes */
  int iLangid,                    /* Language id for current row */
  int iIndex,                     /* Index (0..Fts3Table.nIndex-1) */
  i64 iDocid,                     /* Docid for current row. */
  int iCol,                       /* Column number */
  int iPos                        /* Position */
){
  int i;
  u64 ret = (u64)iDocid;

  ret += (ret<<3) + iLangid;
  ret += (ret<<3) + iIndex;
  ret += (ret<<3) + iCol;
  ret += (ret<<3) + iPos;
  for(i=0; i<nTerm; i++) ret += (ret<<3) + zTerm[i];

  return ret;
}