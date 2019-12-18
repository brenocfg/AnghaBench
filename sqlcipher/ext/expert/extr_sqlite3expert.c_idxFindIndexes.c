#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  hIdx; TYPE_2__* pStatement; int /*<<< orphan*/ * dbm; } ;
typedef  TYPE_1__ sqlite3expert ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_12__ {TYPE_3__* pFirst; } ;
struct TYPE_11__ {char const* zKey; struct TYPE_11__* pNext; } ;
struct TYPE_10__ {void* zIdx; void* zEQP; int /*<<< orphan*/  zSql; struct TYPE_10__* pNext; } ;
typedef  TYPE_2__ IdxStatement ;
typedef  TYPE_3__ IdxHashEntry ;
typedef  TYPE_4__ IdxHash ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int STRLEN (char const*) ; 
 void* idxAppendText (int*,void*,char*,char const*) ; 
 int /*<<< orphan*/  idxFinalize (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idxHashAdd (int*,TYPE_4__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idxHashClear (TYPE_4__*) ; 
 int /*<<< orphan*/  idxHashInit (TYPE_4__*) ; 
 char* idxHashSearch (int /*<<< orphan*/ *,char const*,int) ; 
 int idxPrintfPrepareStmt (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char**,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

int idxFindIndexes(
  sqlite3expert *p,
  char **pzErr                         /* OUT: Error message (sqlite3_malloc) */
){
  IdxStatement *pStmt;
  sqlite3 *dbm = p->dbm;
  int rc = SQLITE_OK;

  IdxHash hIdx;
  idxHashInit(&hIdx);

  for(pStmt=p->pStatement; rc==SQLITE_OK && pStmt; pStmt=pStmt->pNext){
    IdxHashEntry *pEntry;
    sqlite3_stmt *pExplain = 0;
    idxHashClear(&hIdx);
    rc = idxPrintfPrepareStmt(dbm, &pExplain, pzErr,
        "EXPLAIN QUERY PLAN %s", pStmt->zSql
    );
    while( rc==SQLITE_OK && sqlite3_step(pExplain)==SQLITE_ROW ){
      /* int iId = sqlite3_column_int(pExplain, 0); */
      /* int iParent = sqlite3_column_int(pExplain, 1); */
      /* int iNotUsed = sqlite3_column_int(pExplain, 2); */
      const char *zDetail = (const char*)sqlite3_column_text(pExplain, 3);
      int nDetail = STRLEN(zDetail);
      int i;

      for(i=0; i<nDetail; i++){
        const char *zIdx = 0;
        if( memcmp(&zDetail[i], " USING INDEX ", 13)==0 ){
          zIdx = &zDetail[i+13];
        }else if( memcmp(&zDetail[i], " USING COVERING INDEX ", 22)==0 ){
          zIdx = &zDetail[i+22];
        }
        if( zIdx ){
          const char *zSql;
          int nIdx = 0;
          while( zIdx[nIdx]!='\0' && (zIdx[nIdx]!=' ' || zIdx[nIdx+1]!='(') ){
            nIdx++;
          }
          zSql = idxHashSearch(&p->hIdx, zIdx, nIdx);
          if( zSql ){
            idxHashAdd(&rc, &hIdx, zSql, 0);
            if( rc ) goto find_indexes_out;
          }
          break;
        }
      }

      if( zDetail[0]!='-' ){
        pStmt->zEQP = idxAppendText(&rc, pStmt->zEQP, "%s\n", zDetail);
      }
    }

    for(pEntry=hIdx.pFirst; pEntry; pEntry=pEntry->pNext){
      pStmt->zIdx = idxAppendText(&rc, pStmt->zIdx, "%s;\n", pEntry->zKey);
    }

    idxFinalize(&rc, pExplain);
  }

 find_indexes_out:
  idxHashClear(&hIdx);
  return rc;
}