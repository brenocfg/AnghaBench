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
struct TYPE_5__ {int nGroup; int nVal; int /*<<< orphan*/ ** apVal; TYPE_1__** apGroup; } ;
struct TYPE_4__ {int nCol; scalar_t__* aPK; } ;
typedef  TYPE_1__ FuzzChangesetGroup ;
typedef  TYPE_2__ FuzzChangeset ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int fuzzChangeSize (int /*<<< orphan*/ *,int*) ; 
 int fuzzCorrupt () ; 
 scalar_t__ sqlite3_realloc (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int fuzzParseRecord(
  u8 **ppRec,                     /* IN/OUT: Iterator */
  u8 *pEnd,                       /* One byte after end of input data */
  FuzzChangeset *pParse,          /* Changeset parse context */
  int bPkOnly                     /* True if non-PK fields omitted */
){
  int rc = SQLITE_OK;
  FuzzChangesetGroup *pGrp = pParse->apGroup[pParse->nGroup-1];
  int i;
  u8 *p = *ppRec;

  for(i=0; rc==SQLITE_OK && i<pGrp->nCol; i++){
    if( bPkOnly==0 || pGrp->aPK[i] ){
      int sz;
      if( p>=pEnd ) break;
      if( (pParse->nVal & (pParse->nVal-1))==0 ){
        int nNew = pParse->nVal ? pParse->nVal*2 : 4;
        u8 **apNew = (u8**)sqlite3_realloc(pParse->apVal, nNew*sizeof(u8*));
        if( apNew==0 ) return SQLITE_NOMEM;
        pParse->apVal = apNew;
      }
      pParse->apVal[pParse->nVal++] = p;
      rc = fuzzChangeSize(p, &sz);
      p += sz;
    }
  }

  if( rc==SQLITE_OK && i<pGrp->nCol ){
    rc = fuzzCorrupt();
  }

  *ppRec = p;
  return rc;
}