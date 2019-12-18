#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_10__ {TYPE_3__* pTokenizer; } ;
typedef  TYPE_2__ sqlite3_tokenizer_cursor ;
struct TYPE_11__ {TYPE_1__* pModule; } ;
typedef  TYPE_3__ sqlite3_tokenizer ;
struct TYPE_9__ {int (* xOpen ) (TYPE_3__*,char const*,int,TYPE_2__**) ;int (* xNext ) (TYPE_2__*,char const**,int*,int*,int*,int*) ;int /*<<< orphan*/  (* xClose ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  Hash ;
typedef  int /*<<< orphan*/  DocList ;

/* Variables and functions */
 int /*<<< orphan*/  DL_POSITIONS_OFFSETS ; 
 int /*<<< orphan*/  HASH_STRING ; 
 int /*<<< orphan*/ * HashFind (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  HashInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HashInsert (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  docListAddDocid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  docListAddPosOffset (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/ * docListNew (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,char const*,int,TYPE_2__**) ; 
 int stub2 (TYPE_2__*,char const**,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

__attribute__((used)) static int build_terms(Hash *terms, sqlite3_tokenizer *pTokenizer,
                       const char *zText, sqlite_int64 iDocid){
  sqlite3_tokenizer_cursor *pCursor;
  const char *pToken;
  int nTokenBytes;
  int iStartOffset, iEndOffset, iPosition;

  int rc = pTokenizer->pModule->xOpen(pTokenizer, zText, -1, &pCursor);
  if( rc!=SQLITE_OK ) return rc;

  pCursor->pTokenizer = pTokenizer;
  HashInit(terms, HASH_STRING, 1);
  while( SQLITE_OK==pTokenizer->pModule->xNext(pCursor,
                                               &pToken, &nTokenBytes,
                                               &iStartOffset, &iEndOffset,
                                               &iPosition) ){
    DocList *p;

    /* Positions can't be negative; we use -1 as a terminator internally. */
    if( iPosition<0 ) {
      rc = SQLITE_ERROR;  
      goto err;
    }

    p = HashFind(terms, pToken, nTokenBytes);
    if( p==NULL ){
      p = docListNew(DL_POSITIONS_OFFSETS);
      docListAddDocid(p, iDocid);
      HashInsert(terms, pToken, nTokenBytes, p);
    }
    docListAddPosOffset(p, iPosition, iStartOffset, iEndOffset);
  }

err:
  /* TODO(shess) Check return?  Should this be able to cause errors at
  ** this point?  Actually, same question about sqlite3_finalize(),
  ** though one could argue that failure there means that the data is
  ** not durable.  *ponder*
  */
  pTokenizer->pModule->xClose(pCursor);
  return rc;
}