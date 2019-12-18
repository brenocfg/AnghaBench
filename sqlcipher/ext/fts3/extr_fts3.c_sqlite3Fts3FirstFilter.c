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
typedef  int /*<<< orphan*/  sqlite3_int64 ;

/* Variables and functions */
 int /*<<< orphan*/  fts3ColumnlistCopy (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sqlite3Fts3GetVarint (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3Fts3PutVarint (char*,int /*<<< orphan*/ ) ; 

int sqlite3Fts3FirstFilter(
  sqlite3_int64 iDelta,           /* Varint that may be written to pOut */
  char *pList,                    /* Position list (no 0x00 term) */
  int nList,                      /* Size of pList in bytes */
  char *pOut                      /* Write output here */
){
  int nOut = 0;
  int bWritten = 0;               /* True once iDelta has been written */
  char *p = pList;
  char *pEnd = &pList[nList];

  if( *p!=0x01 ){
    if( *p==0x02 ){
      nOut += sqlite3Fts3PutVarint(&pOut[nOut], iDelta);
      pOut[nOut++] = 0x02;
      bWritten = 1;
    }
    fts3ColumnlistCopy(0, &p);
  }

  while( p<pEnd ){
    sqlite3_int64 iCol;
    p++;
    p += sqlite3Fts3GetVarint(p, &iCol);
    if( *p==0x02 ){
      if( bWritten==0 ){
        nOut += sqlite3Fts3PutVarint(&pOut[nOut], iDelta);
        bWritten = 1;
      }
      pOut[nOut++] = 0x01;
      nOut += sqlite3Fts3PutVarint(&pOut[nOut], iCol);
      pOut[nOut++] = 0x02;
    }
    fts3ColumnlistCopy(0, &p);
  }
  if( bWritten ){
    pOut[nOut++] = 0x00;
  }

  return nOut;
}