#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct fts2HashElem {int dummy; } ;
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_21__ {TYPE_5__* pTokenizer; } ;
typedef  TYPE_4__ sqlite3_tokenizer_cursor ;
struct TYPE_22__ {TYPE_3__* pModule; } ;
typedef  TYPE_5__ sqlite3_tokenizer ;
struct TYPE_23__ {int nPendingData; int /*<<< orphan*/  pendingTerms; TYPE_5__* pTokenizer; } ;
typedef  TYPE_6__ fulltext_vtab ;
struct TYPE_19__ {int nData; } ;
struct TYPE_18__ {int /*<<< orphan*/  iPrevDocid; } ;
struct TYPE_24__ {TYPE_2__ b; TYPE_1__ dlw; } ;
struct TYPE_20__ {int (* xOpen ) (TYPE_5__*,char const*,int,TYPE_4__**) ;int (* xNext ) (TYPE_4__*,char const**,int*,int*,int*,int*) ;int /*<<< orphan*/  (* xClose ) (TYPE_4__*) ;} ;
typedef  TYPE_7__ DLCollector ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DEFAULT ; 
 int SQLITE_DONE ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  dlcAddPos (TYPE_7__*,int,int,int,int) ; 
 TYPE_7__* dlcNew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlcNext (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* fts2HashFind (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  fts2HashInsert (int /*<<< orphan*/ *,char const*,int,TYPE_7__*) ; 
 int stub1 (TYPE_5__*,char const*,int,TYPE_4__**) ; 
 int stub2 (TYPE_4__*,char const**,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 

__attribute__((used)) static int buildTerms(fulltext_vtab *v, sqlite_int64 iDocid,
                      const char *zText, int iColumn){
  sqlite3_tokenizer *pTokenizer = v->pTokenizer;
  sqlite3_tokenizer_cursor *pCursor;
  const char *pToken;
  int nTokenBytes;
  int iStartOffset, iEndOffset, iPosition;
  int rc;

  rc = pTokenizer->pModule->xOpen(pTokenizer, zText, -1, &pCursor);
  if( rc!=SQLITE_OK ) return rc;

  pCursor->pTokenizer = pTokenizer;
  while( SQLITE_OK==(rc=pTokenizer->pModule->xNext(pCursor,
                                                   &pToken, &nTokenBytes,
                                                   &iStartOffset, &iEndOffset,
                                                   &iPosition)) ){
    DLCollector *p;
    int nData;                   /* Size of doclist before our update. */

    /* Positions can't be negative; we use -1 as a terminator
     * internally.  Token can't be NULL or empty. */
    if( iPosition<0 || pToken == NULL || nTokenBytes == 0 ){
      rc = SQLITE_ERROR;
      break;
    }

    p = fts2HashFind(&v->pendingTerms, pToken, nTokenBytes);
    if( p==NULL ){
      nData = 0;
      p = dlcNew(iDocid, DL_DEFAULT);
      fts2HashInsert(&v->pendingTerms, pToken, nTokenBytes, p);

      /* Overhead for our hash table entry, the key, and the value. */
      v->nPendingData += sizeof(struct fts2HashElem)+sizeof(*p)+nTokenBytes;
    }else{
      nData = p->b.nData;
      if( p->dlw.iPrevDocid!=iDocid ) dlcNext(p, iDocid);
    }
    if( iColumn>=0 ){
      dlcAddPos(p, iColumn, iPosition, iStartOffset, iEndOffset);
    }

    /* Accumulate data added by dlcNew or dlcNext, and dlcAddPos. */
    v->nPendingData += p->b.nData-nData;
  }

  /* TODO(shess) Check return?  Should this be able to cause errors at
  ** this point?  Actually, same question about sqlite3_finalize(),
  ** though one could argue that failure there means that the data is
  ** not durable.  *ponder*
  */
  pTokenizer->pModule->xClose(pCursor);
  if( SQLITE_DONE == rc ) return SQLITE_OK;
  return rc;
}