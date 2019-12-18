#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_14__ {int /*<<< orphan*/  n; int /*<<< orphan*/  p; } ;
struct TYPE_11__ {scalar_t__ pVtab; } ;
struct TYPE_13__ {int /*<<< orphan*/  pExpr; TYPE_2__ base; } ;
struct TYPE_12__ {TYPE_1__* pConfig; } ;
struct TYPE_10__ {int eDetail; } ;
typedef  TYPE_3__ Fts5Table ;
typedef  TYPE_4__ Fts5Cursor ;
typedef  TYPE_5__ Fts5Buffer ;

/* Variables and functions */
#define  FTS5_DETAIL_COLUMNS 129 
#define  FTS5_DETAIL_FULL 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferAppendBlob (int*,TYPE_5__*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferAppendVarint (int*,TYPE_5__*,int) ; 
 int sqlite3Fts5ExprPhraseCollist (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,int*) ; 
 int sqlite3Fts5ExprPhraseCount (int /*<<< orphan*/ ) ; 
 int sqlite3Fts5ExprPoslist (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5PoslistBlob(sqlite3_context *pCtx, Fts5Cursor *pCsr){
  int i;
  int rc = SQLITE_OK;
  int nPhrase = sqlite3Fts5ExprPhraseCount(pCsr->pExpr);
  Fts5Buffer val;

  memset(&val, 0, sizeof(Fts5Buffer));
  switch( ((Fts5Table*)(pCsr->base.pVtab))->pConfig->eDetail ){
    case FTS5_DETAIL_FULL:

      /* Append the varints */
      for(i=0; i<(nPhrase-1); i++){
        const u8 *dummy;
        int nByte = sqlite3Fts5ExprPoslist(pCsr->pExpr, i, &dummy);
        sqlite3Fts5BufferAppendVarint(&rc, &val, nByte);
      }

      /* Append the position lists */
      for(i=0; i<nPhrase; i++){
        const u8 *pPoslist;
        int nPoslist;
        nPoslist = sqlite3Fts5ExprPoslist(pCsr->pExpr, i, &pPoslist);
        sqlite3Fts5BufferAppendBlob(&rc, &val, nPoslist, pPoslist);
      }
      break;

    case FTS5_DETAIL_COLUMNS:

      /* Append the varints */
      for(i=0; rc==SQLITE_OK && i<(nPhrase-1); i++){
        const u8 *dummy;
        int nByte;
        rc = sqlite3Fts5ExprPhraseCollist(pCsr->pExpr, i, &dummy, &nByte);
        sqlite3Fts5BufferAppendVarint(&rc, &val, nByte);
      }

      /* Append the position lists */
      for(i=0; rc==SQLITE_OK && i<nPhrase; i++){
        const u8 *pPoslist;
        int nPoslist;
        rc = sqlite3Fts5ExprPhraseCollist(pCsr->pExpr, i, &pPoslist, &nPoslist);
        sqlite3Fts5BufferAppendBlob(&rc, &val, nPoslist, pPoslist);
      }
      break;

    default:
      break;
  }

  sqlite3_result_blob(pCtx, val.p, val.n, sqlite3_free);
  return rc;
}