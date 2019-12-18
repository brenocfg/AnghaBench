#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  iPrevId; } ;
struct TYPE_7__ {int bFreeList; char* pList; int nList; int /*<<< orphan*/  iDocid; } ;
struct TYPE_9__ {int nToken; int iDoclistToken; TYPE_1__ doclist; TYPE_2__* aToken; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pDeferred; } ;
typedef  TYPE_2__ Fts3PhraseToken ;
typedef  TYPE_3__ Fts3Phrase ;
typedef  int /*<<< orphan*/  Fts3DeferredToken ;
typedef  TYPE_4__ Fts3Cursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fts3PoslistPhraseMerge (char**,int,int /*<<< orphan*/ ,int,char**,char**) ; 
 int sqlite3Fts3DeferredTokenList (int /*<<< orphan*/ *,char**,int*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 scalar_t__ sqlite3_malloc (int) ; 

__attribute__((used)) static int fts3EvalDeferredPhrase(Fts3Cursor *pCsr, Fts3Phrase *pPhrase){
  int iToken;                     /* Used to iterate through phrase tokens */
  char *aPoslist = 0;             /* Position list for deferred tokens */
  int nPoslist = 0;               /* Number of bytes in aPoslist */
  int iPrev = -1;                 /* Token number of previous deferred token */

  assert( pPhrase->doclist.bFreeList==0 );

  for(iToken=0; iToken<pPhrase->nToken; iToken++){
    Fts3PhraseToken *pToken = &pPhrase->aToken[iToken];
    Fts3DeferredToken *pDeferred = pToken->pDeferred;

    if( pDeferred ){
      char *pList;
      int nList;
      int rc = sqlite3Fts3DeferredTokenList(pDeferred, &pList, &nList);
      if( rc!=SQLITE_OK ) return rc;

      if( pList==0 ){
        sqlite3_free(aPoslist);
        pPhrase->doclist.pList = 0;
        pPhrase->doclist.nList = 0;
        return SQLITE_OK;

      }else if( aPoslist==0 ){
        aPoslist = pList;
        nPoslist = nList;

      }else{
        char *aOut = pList;
        char *p1 = aPoslist;
        char *p2 = aOut;

        assert( iPrev>=0 );
        fts3PoslistPhraseMerge(&aOut, iToken-iPrev, 0, 1, &p1, &p2);
        sqlite3_free(aPoslist);
        aPoslist = pList;
        nPoslist = (int)(aOut - aPoslist);
        if( nPoslist==0 ){
          sqlite3_free(aPoslist);
          pPhrase->doclist.pList = 0;
          pPhrase->doclist.nList = 0;
          return SQLITE_OK;
        }
      }
      iPrev = iToken;
    }
  }

  if( iPrev>=0 ){
    int nMaxUndeferred = pPhrase->iDoclistToken;
    if( nMaxUndeferred<0 ){
      pPhrase->doclist.pList = aPoslist;
      pPhrase->doclist.nList = nPoslist;
      pPhrase->doclist.iDocid = pCsr->iPrevId;
      pPhrase->doclist.bFreeList = 1;
    }else{
      int nDistance;
      char *p1;
      char *p2;
      char *aOut;

      if( nMaxUndeferred>iPrev ){
        p1 = aPoslist;
        p2 = pPhrase->doclist.pList;
        nDistance = nMaxUndeferred - iPrev;
      }else{
        p1 = pPhrase->doclist.pList;
        p2 = aPoslist;
        nDistance = iPrev - nMaxUndeferred;
      }

      aOut = (char *)sqlite3_malloc(nPoslist+8);
      if( !aOut ){
        sqlite3_free(aPoslist);
        return SQLITE_NOMEM;
      }
      
      pPhrase->doclist.pList = aOut;
      if( fts3PoslistPhraseMerge(&aOut, nDistance, 0, 1, &p1, &p2) ){
        pPhrase->doclist.bFreeList = 1;
        pPhrase->doclist.nList = (int)(aOut - pPhrase->doclist.pList);
      }else{
        sqlite3_free(aOut);
        pPhrase->doclist.pList = 0;
        pPhrase->doclist.nList = 0;
      }
      sqlite3_free(aPoslist);
    }
  }

  return SQLITE_OK;
}