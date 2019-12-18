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
typedef  int u64 ;
struct TYPE_10__ {int (* xNext ) (int /*<<< orphan*/ *,char const**,int*,int*,int*,int*) ;int /*<<< orphan*/  (* xClose ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ sqlite3_tokenizer_module ;
typedef  int /*<<< orphan*/  sqlite3_tokenizer_cursor ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_12__ {TYPE_2__* pModule; } ;
struct TYPE_11__ {int iPrevLangid; int nIndex; int nColumn; scalar_t__* abNotindexed; TYPE_1__* aIndex; TYPE_4__* pTokenizer; int /*<<< orphan*/  db; int /*<<< orphan*/  zReadExprlist; } ;
struct TYPE_9__ {int nPrefix; } ;
typedef  TYPE_3__ Fts3Table ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQL_SELECT_ALL_LANGID ; 
 int fts3ChecksumEntry (char const*,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 int fts3ChecksumIndex (TYPE_3__*,int,int,int*) ; 
 int fts3SqlStmt (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int langidFromSelect (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int sqlite3Fts3OpenTokenizer (TYPE_4__*,int,char const*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,char const**,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3IntegrityCheck(Fts3Table *p, int *pbOk){
  int rc = SQLITE_OK;             /* Return code */
  u64 cksum1 = 0;                 /* Checksum based on FTS index contents */
  u64 cksum2 = 0;                 /* Checksum based on %_content contents */
  sqlite3_stmt *pAllLangid = 0;   /* Statement to return all language-ids */

  /* This block calculates the checksum according to the FTS index. */
  rc = fts3SqlStmt(p, SQL_SELECT_ALL_LANGID, &pAllLangid, 0);
  if( rc==SQLITE_OK ){
    int rc2;
    sqlite3_bind_int(pAllLangid, 1, p->iPrevLangid);
    sqlite3_bind_int(pAllLangid, 2, p->nIndex);
    while( rc==SQLITE_OK && sqlite3_step(pAllLangid)==SQLITE_ROW ){
      int iLangid = sqlite3_column_int(pAllLangid, 0);
      int i;
      for(i=0; i<p->nIndex; i++){
        cksum1 = cksum1 ^ fts3ChecksumIndex(p, iLangid, i, &rc);
      }
    }
    rc2 = sqlite3_reset(pAllLangid);
    if( rc==SQLITE_OK ) rc = rc2;
  }

  /* This block calculates the checksum according to the %_content table */
  if( rc==SQLITE_OK ){
    sqlite3_tokenizer_module const *pModule = p->pTokenizer->pModule;
    sqlite3_stmt *pStmt = 0;
    char *zSql;
   
    zSql = sqlite3_mprintf("SELECT %s" , p->zReadExprlist);
    if( !zSql ){
      rc = SQLITE_NOMEM;
    }else{
      rc = sqlite3_prepare_v2(p->db, zSql, -1, &pStmt, 0);
      sqlite3_free(zSql);
    }

    while( rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(pStmt) ){
      i64 iDocid = sqlite3_column_int64(pStmt, 0);
      int iLang = langidFromSelect(p, pStmt);
      int iCol;

      for(iCol=0; rc==SQLITE_OK && iCol<p->nColumn; iCol++){
        if( p->abNotindexed[iCol]==0 ){
          const char *zText = (const char *)sqlite3_column_text(pStmt, iCol+1);
          int nText = sqlite3_column_bytes(pStmt, iCol+1);
          sqlite3_tokenizer_cursor *pT = 0;

          rc = sqlite3Fts3OpenTokenizer(p->pTokenizer, iLang, zText, nText,&pT);
          while( rc==SQLITE_OK ){
            char const *zToken;       /* Buffer containing token */
            int nToken = 0;           /* Number of bytes in token */
            int iDum1 = 0, iDum2 = 0; /* Dummy variables */
            int iPos = 0;             /* Position of token in zText */

            rc = pModule->xNext(pT, &zToken, &nToken, &iDum1, &iDum2, &iPos);
            if( rc==SQLITE_OK ){
              int i;
              cksum2 = cksum2 ^ fts3ChecksumEntry(
                  zToken, nToken, iLang, 0, iDocid, iCol, iPos
              );
              for(i=1; i<p->nIndex; i++){
                if( p->aIndex[i].nPrefix<=nToken ){
                  cksum2 = cksum2 ^ fts3ChecksumEntry(
                      zToken, p->aIndex[i].nPrefix, iLang, i, iDocid, iCol, iPos
                  );
                }
              }
            }
          }
          if( pT ) pModule->xClose(pT);
          if( rc==SQLITE_DONE ) rc = SQLITE_OK;
        }
      }
    }

    sqlite3_finalize(pStmt);
  }

  *pbOk = (cksum1==cksum2);
  return rc;
}