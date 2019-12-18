#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nCol; int /*<<< orphan*/ * azCol; } ;
struct TYPE_9__ {scalar_t__ rc; TYPE_3__* pConfig; } ;
struct TYPE_8__ {int /*<<< orphan*/  n; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ Fts5Token ;
typedef  TYPE_2__ Fts5Parse ;
typedef  TYPE_3__ Fts5Config ;
typedef  char Fts5Colset ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 char* fts5ParseColset (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  sqlite3Fts5Dequote (char*) ; 
 int /*<<< orphan*/  sqlite3Fts5ParseError (TYPE_2__*,char*,char*) ; 
 char* sqlite3Fts5Strndup (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 scalar_t__ sqlite3_stricmp (int /*<<< orphan*/ ,char*) ; 

Fts5Colset *sqlite3Fts5ParseColset(
  Fts5Parse *pParse,              /* Store SQLITE_NOMEM here if required */
  Fts5Colset *pColset,            /* Existing colset object */
  Fts5Token *p
){
  Fts5Colset *pRet = 0;
  int iCol;
  char *z;                        /* Dequoted copy of token p */

  z = sqlite3Fts5Strndup(&pParse->rc, p->p, p->n);
  if( pParse->rc==SQLITE_OK ){
    Fts5Config *pConfig = pParse->pConfig;
    sqlite3Fts5Dequote(z);
    for(iCol=0; iCol<pConfig->nCol; iCol++){
      if( 0==sqlite3_stricmp(pConfig->azCol[iCol], z) ) break;
    }
    if( iCol==pConfig->nCol ){
      sqlite3Fts5ParseError(pParse, "no such column: %s", z);
    }else{
      pRet = fts5ParseColset(pParse, pColset, iCol);
    }
    sqlite3_free(z);
  }

  if( pRet==0 ){
    assert( pParse->rc!=SQLITE_OK );
    sqlite3_free(pColset);
  }

  return pRet;
}