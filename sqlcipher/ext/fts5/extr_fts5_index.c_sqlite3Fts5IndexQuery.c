#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_25__ {scalar_t__* p; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_24__ {scalar_t__ bPrefixIndex; int nPrefix; int* aPrefix; } ;
struct TYPE_23__ {scalar_t__ rc; TYPE_5__* pConfig; } ;
struct TYPE_22__ {scalar_t__ pColset; int /*<<< orphan*/  (* xSetOutputs ) (TYPE_3__*,TYPE_2__*) ;TYPE_1__* aFirst; TYPE_2__* aSeg; } ;
struct TYPE_21__ {scalar_t__ pLeaf; } ;
struct TYPE_20__ {size_t iFirst; } ;
typedef  int /*<<< orphan*/  Fts5Structure ;
typedef  TYPE_2__ Fts5SegIter ;
typedef  TYPE_3__ Fts5Iter ;
typedef  int /*<<< orphan*/  Fts5IndexIter ;
typedef  TYPE_4__ Fts5Index ;
typedef  TYPE_5__ Fts5Config ;
typedef  int /*<<< orphan*/  Fts5Colset ;
typedef  TYPE_6__ Fts5Buffer ;

/* Variables and functions */
 int FTS5INDEX_QUERY_DESC ; 
 int FTS5INDEX_QUERY_PREFIX ; 
 int FTS5INDEX_QUERY_SCAN ; 
 int FTS5INDEX_QUERY_SKIPEMPTY ; 
 int FTS5INDEX_QUERY_TEST_NOIDX ; 
 scalar_t__ FTS5_MAIN_PREFIX ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5CloseReader (TYPE_4__*) ; 
 int fts5IndexCharlen (char const*,int) ; 
 int fts5IndexReturn (TYPE_4__*) ; 
 int /*<<< orphan*/  fts5IterSetOutputCb (scalar_t__*,TYPE_3__*) ; 
 int /*<<< orphan*/  fts5MultiIterNew (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__*,int,int,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  fts5SetupPrefixIter (TYPE_4__*,int,scalar_t__*,int,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/ * fts5StructureRead (TYPE_4__*) ; 
 int /*<<< orphan*/  fts5StructureRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferFree (TYPE_6__*) ; 
 scalar_t__ sqlite3Fts5BufferSize (scalar_t__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  sqlite3Fts5IterClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*) ; 

int sqlite3Fts5IndexQuery(
  Fts5Index *p,                   /* FTS index to query */
  const char *pToken, int nToken, /* Token (or prefix) to query for */
  int flags,                      /* Mask of FTS5INDEX_QUERY_X flags */
  Fts5Colset *pColset,            /* Match these columns only */
  Fts5IndexIter **ppIter          /* OUT: New iterator object */
){
  Fts5Config *pConfig = p->pConfig;
  Fts5Iter *pRet = 0;
  Fts5Buffer buf = {0, 0, 0};

  /* If the QUERY_SCAN flag is set, all other flags must be clear. */
  assert( (flags & FTS5INDEX_QUERY_SCAN)==0 || flags==FTS5INDEX_QUERY_SCAN );

  if( sqlite3Fts5BufferSize(&p->rc, &buf, nToken+1)==0 ){
    int iIdx = 0;                 /* Index to search */
    if( nToken ) memcpy(&buf.p[1], pToken, nToken);

    /* Figure out which index to search and set iIdx accordingly. If this
    ** is a prefix query for which there is no prefix index, set iIdx to
    ** greater than pConfig->nPrefix to indicate that the query will be
    ** satisfied by scanning multiple terms in the main index.
    **
    ** If the QUERY_TEST_NOIDX flag was specified, then this must be a
    ** prefix-query. Instead of using a prefix-index (if one exists), 
    ** evaluate the prefix query using the main FTS index. This is used
    ** for internal sanity checking by the integrity-check in debug 
    ** mode only.  */
#ifdef SQLITE_DEBUG
    if( pConfig->bPrefixIndex==0 || (flags & FTS5INDEX_QUERY_TEST_NOIDX) ){
      assert( flags & FTS5INDEX_QUERY_PREFIX );
      iIdx = 1+pConfig->nPrefix;
    }else
#endif
    if( flags & FTS5INDEX_QUERY_PREFIX ){
      int nChar = fts5IndexCharlen(pToken, nToken);
      for(iIdx=1; iIdx<=pConfig->nPrefix; iIdx++){
        if( pConfig->aPrefix[iIdx-1]==nChar ) break;
      }
    }

    if( iIdx<=pConfig->nPrefix ){
      /* Straight index lookup */
      Fts5Structure *pStruct = fts5StructureRead(p);
      buf.p[0] = (u8)(FTS5_MAIN_PREFIX + iIdx);
      if( pStruct ){
        fts5MultiIterNew(p, pStruct, flags | FTS5INDEX_QUERY_SKIPEMPTY, 
            pColset, buf.p, nToken+1, -1, 0, &pRet
        );
        fts5StructureRelease(pStruct);
      }
    }else{
      /* Scan multiple terms in the main index */
      int bDesc = (flags & FTS5INDEX_QUERY_DESC)!=0;
      buf.p[0] = FTS5_MAIN_PREFIX;
      fts5SetupPrefixIter(p, bDesc, buf.p, nToken+1, pColset, &pRet);
      assert( p->rc!=SQLITE_OK || pRet->pColset==0 );
      fts5IterSetOutputCb(&p->rc, pRet);
      if( p->rc==SQLITE_OK ){
        Fts5SegIter *pSeg = &pRet->aSeg[pRet->aFirst[1].iFirst];
        if( pSeg->pLeaf ) pRet->xSetOutputs(pRet, pSeg);
      }
    }

    if( p->rc ){
      sqlite3Fts5IterClose((Fts5IndexIter*)pRet);
      pRet = 0;
      fts5CloseReader(p);
    }

    *ppIter = (Fts5IndexIter*)pRet;
    sqlite3Fts5BufferFree(&buf);
  }
  return fts5IndexReturn(p);
}