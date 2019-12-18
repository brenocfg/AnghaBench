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
typedef  int sqlite3_int64 ;
struct TYPE_3__ {char* pRead; int iPos; } ;
typedef  TYPE_1__ LcsIterator ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3Fts3GetVarint (char*,int*) ; 

__attribute__((used)) static int fts3LcsIteratorAdvance(LcsIterator *pIter){
  char *pRead = pIter->pRead;
  sqlite3_int64 iRead;
  int rc = 0;

  pRead += sqlite3Fts3GetVarint(pRead, &iRead);
  if( iRead==0 || iRead==1 ){
    pRead = 0;
    rc = 1;
  }else{
    pIter->iPos += (int)(iRead-2);
  }

  pIter->pRead = pRead;
  return rc;
}