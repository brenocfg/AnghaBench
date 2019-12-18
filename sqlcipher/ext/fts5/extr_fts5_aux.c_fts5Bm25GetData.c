#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_11__ {int nPhrase; double* aIDF; double* aFreq; double avgdl; } ;
struct TYPE_10__ {int (* xPhraseCount ) (int /*<<< orphan*/ *) ;int (* xRowCount ) (int /*<<< orphan*/ *,scalar_t__*) ;int (* xColumnTotalSize ) (int /*<<< orphan*/ *,int,scalar_t__*) ;int (* xQueryPhrase ) (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ;int (* xSetAuxdata ) (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/  (*) (TYPE_2__*)) ;TYPE_2__* (* xGetAuxdata ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ Fts5ExtensionApi ;
typedef  int /*<<< orphan*/  Fts5Context ;
typedef  TYPE_2__ Fts5Bm25Data ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5CountCb ; 
 double log (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 scalar_t__ sqlite3_malloc64 (scalar_t__) ; 
 TYPE_2__* stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *) ; 
 int stub3 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int stub4 (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int stub5 (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int stub6 (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/  (*) (TYPE_2__*)) ; 

__attribute__((used)) static int fts5Bm25GetData(
  const Fts5ExtensionApi *pApi, 
  Fts5Context *pFts,
  Fts5Bm25Data **ppData           /* OUT: bm25-data object for this query */
){
  int rc = SQLITE_OK;             /* Return code */
  Fts5Bm25Data *p;                /* Object to return */

  p = pApi->xGetAuxdata(pFts, 0);
  if( p==0 ){
    int nPhrase;                  /* Number of phrases in query */
    sqlite3_int64 nRow = 0;       /* Number of rows in table */
    sqlite3_int64 nToken = 0;     /* Number of tokens in table */
    sqlite3_int64 nByte;          /* Bytes of space to allocate */
    int i;

    /* Allocate the Fts5Bm25Data object */
    nPhrase = pApi->xPhraseCount(pFts);
    nByte = sizeof(Fts5Bm25Data) + nPhrase*2*sizeof(double);
    p = (Fts5Bm25Data*)sqlite3_malloc64(nByte);
    if( p==0 ){
      rc = SQLITE_NOMEM;
    }else{
      memset(p, 0, (size_t)nByte);
      p->nPhrase = nPhrase;
      p->aIDF = (double*)&p[1];
      p->aFreq = &p->aIDF[nPhrase];
    }

    /* Calculate the average document length for this FTS5 table */
    if( rc==SQLITE_OK ) rc = pApi->xRowCount(pFts, &nRow);
    assert( rc!=SQLITE_OK || nRow>0 );
    if( rc==SQLITE_OK ) rc = pApi->xColumnTotalSize(pFts, -1, &nToken);
    if( rc==SQLITE_OK ) p->avgdl = (double)nToken  / (double)nRow;

    /* Calculate an IDF for each phrase in the query */
    for(i=0; rc==SQLITE_OK && i<nPhrase; i++){
      sqlite3_int64 nHit = 0;
      rc = pApi->xQueryPhrase(pFts, i, (void*)&nHit, fts5CountCb);
      if( rc==SQLITE_OK ){
        /* Calculate the IDF (Inverse Document Frequency) for phrase i.
        ** This is done using the standard BM25 formula as found on wikipedia:
        **
        **   IDF = log( (N - nHit + 0.5) / (nHit + 0.5) )
        **
        ** where "N" is the total number of documents in the set and nHit
        ** is the number that contain at least one instance of the phrase
        ** under consideration.
        **
        ** The problem with this is that if (N < 2*nHit), the IDF is 
        ** negative. Which is undesirable. So the mimimum allowable IDF is
        ** (1e-6) - roughly the same as a term that appears in just over
        ** half of set of 5,000,000 documents.  */
        double idf = log( (nRow - nHit + 0.5) / (nHit + 0.5) );
        if( idf<=0.0 ) idf = 1e-6;
        p->aIDF[i] = idf;
      }
    }

    if( rc!=SQLITE_OK ){
      sqlite3_free(p);
    }else{
      rc = pApi->xSetAuxdata(pFts, p, sqlite3_free);
    }
    if( rc!=SQLITE_OK ) p = 0;
  }
  *ppData = p;
  return rc;
}