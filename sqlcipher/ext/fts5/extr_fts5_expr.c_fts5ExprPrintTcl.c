#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nPhrase; char* nNear; TYPE_3__** apPhrase; TYPE_1__* pColset; } ;
struct TYPE_10__ {int eType; int nChild; struct TYPE_10__** apChild; TYPE_5__* pNear; } ;
struct TYPE_9__ {int nTerm; TYPE_2__* aTerm; } ;
struct TYPE_8__ {char* zTerm; scalar_t__ bPrefix; } ;
struct TYPE_7__ {int* aiCol; int nCol; } ;
typedef  TYPE_3__ Fts5ExprPhrase ;
typedef  TYPE_4__ Fts5ExprNode ;
typedef  TYPE_5__ Fts5ExprNearset ;
typedef  int /*<<< orphan*/  Fts5Config ;

/* Variables and functions */
#define  FTS5_AND 129 
#define  FTS5_NOT 128 
 int FTS5_OR ; 
 int FTS5_STRING ; 
 int FTS5_TERM ; 
 int /*<<< orphan*/  assert (int) ; 
 char* fts5PrintfAppend (char*,char*,...) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 

__attribute__((used)) static char *fts5ExprPrintTcl(
  Fts5Config *pConfig, 
  const char *zNearsetCmd,
  Fts5ExprNode *pExpr
){
  char *zRet = 0;
  if( pExpr->eType==FTS5_STRING || pExpr->eType==FTS5_TERM ){
    Fts5ExprNearset *pNear = pExpr->pNear;
    int i; 
    int iTerm;

    zRet = fts5PrintfAppend(zRet, "%s ", zNearsetCmd);
    if( zRet==0 ) return 0;
    if( pNear->pColset ){
      int *aiCol = pNear->pColset->aiCol;
      int nCol = pNear->pColset->nCol;
      if( nCol==1 ){
        zRet = fts5PrintfAppend(zRet, "-col %d ", aiCol[0]);
      }else{
        zRet = fts5PrintfAppend(zRet, "-col {%d", aiCol[0]);
        for(i=1; i<pNear->pColset->nCol; i++){
          zRet = fts5PrintfAppend(zRet, " %d", aiCol[i]);
        }
        zRet = fts5PrintfAppend(zRet, "} ");
      }
      if( zRet==0 ) return 0;
    }

    if( pNear->nPhrase>1 ){
      zRet = fts5PrintfAppend(zRet, "-near %d ", pNear->nNear);
      if( zRet==0 ) return 0;
    }

    zRet = fts5PrintfAppend(zRet, "--");
    if( zRet==0 ) return 0;

    for(i=0; i<pNear->nPhrase; i++){
      Fts5ExprPhrase *pPhrase = pNear->apPhrase[i];

      zRet = fts5PrintfAppend(zRet, " {");
      for(iTerm=0; zRet && iTerm<pPhrase->nTerm; iTerm++){
        char *zTerm = pPhrase->aTerm[iTerm].zTerm;
        zRet = fts5PrintfAppend(zRet, "%s%s", iTerm==0?"":" ", zTerm);
        if( pPhrase->aTerm[iTerm].bPrefix ){
          zRet = fts5PrintfAppend(zRet, "*");
        }
      }

      if( zRet ) zRet = fts5PrintfAppend(zRet, "}");
      if( zRet==0 ) return 0;
    }

  }else{
    char const *zOp = 0;
    int i;
    switch( pExpr->eType ){
      case FTS5_AND: zOp = "AND"; break;
      case FTS5_NOT: zOp = "NOT"; break;
      default: 
        assert( pExpr->eType==FTS5_OR );
        zOp = "OR"; 
        break;
    }

    zRet = sqlite3_mprintf("%s", zOp);
    for(i=0; zRet && i<pExpr->nChild; i++){
      char *z = fts5ExprPrintTcl(pConfig, zNearsetCmd, pExpr->apChild[i]);
      if( !z ){
        sqlite3_free(zRet);
        zRet = 0;
      }else{
        zRet = fts5PrintfAppend(zRet, " [%z]", z);
      }
    }
  }

  return zRet;
}