#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* aAll; int nAll; } ;
struct TYPE_8__ {int iDoclistToken; TYPE_1__ doclist; } ;
struct TYPE_7__ {int /*<<< orphan*/  bDescIdx; } ;
typedef  TYPE_2__ Fts3Table ;
typedef  TYPE_3__ Fts3Phrase ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3DoclistPhraseMerge (int /*<<< orphan*/ ,int,char*,int,char**,int*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 

__attribute__((used)) static int fts3EvalPhraseMergeToken(
  Fts3Table *pTab,                /* FTS Table pointer */
  Fts3Phrase *p,                  /* Phrase to merge pList/nList into */
  int iToken,                     /* Token pList/nList corresponds to */
  char *pList,                    /* Pointer to doclist */
  int nList                       /* Number of bytes in pList */
){
  int rc = SQLITE_OK;
  assert( iToken!=p->iDoclistToken );

  if( pList==0 ){
    sqlite3_free(p->doclist.aAll);
    p->doclist.aAll = 0;
    p->doclist.nAll = 0;
  }

  else if( p->iDoclistToken<0 ){
    p->doclist.aAll = pList;
    p->doclist.nAll = nList;
  }

  else if( p->doclist.aAll==0 ){
    sqlite3_free(pList);
  }

  else {
    char *pLeft;
    char *pRight;
    int nLeft;
    int nRight;
    int nDiff;

    if( p->iDoclistToken<iToken ){
      pLeft = p->doclist.aAll;
      nLeft = p->doclist.nAll;
      pRight = pList;
      nRight = nList;
      nDiff = iToken - p->iDoclistToken;
    }else{
      pRight = p->doclist.aAll;
      nRight = p->doclist.nAll;
      pLeft = pList;
      nLeft = nList;
      nDiff = p->iDoclistToken - iToken;
    }

    rc = fts3DoclistPhraseMerge(
        pTab->bDescIdx, nDiff, pLeft, nLeft, &pRight, &nRight
    );
    sqlite3_free(pLeft);
    p->doclist.aAll = pRight;
    p->doclist.nAll = nRight;
  }

  if( iToken>p->iDoclistToken ) p->iDoclistToken = iToken;
  return rc;
}