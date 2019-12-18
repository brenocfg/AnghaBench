#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_60__   TYPE_7__ ;
typedef  struct TYPE_59__   TYPE_6__ ;
typedef  struct TYPE_58__   TYPE_5__ ;
typedef  struct TYPE_57__   TYPE_4__ ;
typedef  struct TYPE_56__   TYPE_3__ ;
typedef  struct TYPE_55__   TYPE_2__ ;
typedef  struct TYPE_54__   TYPE_1__ ;
typedef  struct TYPE_53__   TYPE_14__ ;
typedef  struct TYPE_52__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  doclist ;
struct TYPE_60__ {scalar_t__ n; int /*<<< orphan*/  p; } ;
struct TYPE_57__ {scalar_t__ nData; scalar_t__ iRowid; } ;
struct TYPE_59__ {TYPE_4__ base; int /*<<< orphan*/  (* xSetOutputs ) (TYPE_6__*,TYPE_11__*) ;TYPE_2__* aFirst; TYPE_11__* aSeg; } ;
struct TYPE_58__ {scalar_t__ rc; TYPE_1__* pConfig; } ;
struct TYPE_56__ {int n; int /*<<< orphan*/ * p; } ;
struct TYPE_55__ {size_t iFirst; } ;
struct TYPE_54__ {scalar_t__ eDetail; } ;
struct TYPE_53__ {int nn; int szLeaf; int /*<<< orphan*/ * p; } ;
struct TYPE_52__ {TYPE_3__ term; } ;
typedef  int /*<<< orphan*/  Fts5Structure ;
typedef  TYPE_11__ Fts5SegIter ;
typedef  TYPE_6__ Fts5Iter ;
typedef  TYPE_5__ Fts5Index ;
typedef  TYPE_14__ Fts5Data ;
typedef  int /*<<< orphan*/  Fts5Colset ;
typedef  TYPE_7__ Fts5Buffer ;

/* Variables and functions */
 int FTS5INDEX_QUERY_NOOUTPUT ; 
 int FTS5INDEX_QUERY_SCAN ; 
 int FTS5INDEX_QUERY_SKIPEMPTY ; 
 int FTS5_DATA_ZERO_PADDING ; 
 scalar_t__ FTS5_DETAIL_NONE ; 
 int MIN (int,int) ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_nc (int) ; 
 void fts5AppendPoslist (TYPE_5__*,i64,TYPE_6__*,TYPE_7__*) ; 
 void fts5AppendRowid (TYPE_5__*,i64,TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  fts5BufferFree (TYPE_7__*) ; 
 int /*<<< orphan*/  fts5BufferSwap (TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  fts5BufferZero (TYPE_7__*) ; 
 TYPE_14__* fts5IdxMalloc (TYPE_5__*,int) ; 
 int /*<<< orphan*/  fts5IterSetOutputCb (scalar_t__*,TYPE_6__*) ; 
 void fts5MergePrefixLists (TYPE_5__*,TYPE_7__*,TYPE_7__*) ; 
 void fts5MergeRowidLists (TYPE_5__*,TYPE_7__*,TYPE_7__*) ; 
 scalar_t__ fts5MultiIterEof (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  fts5MultiIterFree (TYPE_6__*) ; 
 int /*<<< orphan*/  fts5MultiIterNew (TYPE_5__*,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  fts5MultiIterNew2 (TYPE_5__*,TYPE_14__*,int,TYPE_6__**) ; 
 int /*<<< orphan*/  fts5MultiIterNext2 (TYPE_5__*,TYPE_6__*,int*) ; 
 int /*<<< orphan*/ * fts5StructureRead (TYPE_5__*) ; 
 int /*<<< orphan*/  fts5StructureRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_7__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,TYPE_11__*) ; 

__attribute__((used)) static void fts5SetupPrefixIter(
  Fts5Index *p,                   /* Index to read from */
  int bDesc,                      /* True for "ORDER BY rowid DESC" */
  const u8 *pToken,               /* Buffer containing prefix to match */
  int nToken,                     /* Size of buffer pToken in bytes */
  Fts5Colset *pColset,            /* Restrict matches to these columns */
  Fts5Iter **ppIter          /* OUT: New iterator */
){
  Fts5Structure *pStruct;
  Fts5Buffer *aBuf;
  const int nBuf = 32;

  void (*xMerge)(Fts5Index*, Fts5Buffer*, Fts5Buffer*);
  void (*xAppend)(Fts5Index*, i64, Fts5Iter*, Fts5Buffer*);
  if( p->pConfig->eDetail==FTS5_DETAIL_NONE ){
    xMerge = fts5MergeRowidLists;
    xAppend = fts5AppendRowid;
  }else{
    xMerge = fts5MergePrefixLists;
    xAppend = fts5AppendPoslist;
  }

  aBuf = (Fts5Buffer*)fts5IdxMalloc(p, sizeof(Fts5Buffer)*nBuf);
  pStruct = fts5StructureRead(p);

  if( aBuf && pStruct ){
    const int flags = FTS5INDEX_QUERY_SCAN 
                    | FTS5INDEX_QUERY_SKIPEMPTY 
                    | FTS5INDEX_QUERY_NOOUTPUT;
    int i;
    i64 iLastRowid = 0;
    Fts5Iter *p1 = 0;     /* Iterator used to gather data from index */
    Fts5Data *pData;
    Fts5Buffer doclist;
    int bNewTerm = 1;

    memset(&doclist, 0, sizeof(doclist));
    fts5MultiIterNew(p, pStruct, flags, pColset, pToken, nToken, -1, 0, &p1);
    fts5IterSetOutputCb(&p->rc, p1);
    for( /* no-op */ ;
        fts5MultiIterEof(p, p1)==0;
        fts5MultiIterNext2(p, p1, &bNewTerm)
    ){
      Fts5SegIter *pSeg = &p1->aSeg[ p1->aFirst[1].iFirst ];
      int nTerm = pSeg->term.n;
      const u8 *pTerm = pSeg->term.p;
      p1->xSetOutputs(p1, pSeg);

      assert_nc( memcmp(pToken, pTerm, MIN(nToken, nTerm))<=0 );
      if( bNewTerm ){
        if( nTerm<nToken || memcmp(pToken, pTerm, nToken) ) break;
      }

      if( p1->base.nData==0 ) continue;

      if( p1->base.iRowid<=iLastRowid && doclist.n>0 ){
        for(i=0; p->rc==SQLITE_OK && doclist.n; i++){
          assert( i<nBuf );
          if( aBuf[i].n==0 ){
            fts5BufferSwap(&doclist, &aBuf[i]);
            fts5BufferZero(&doclist);
          }else{
            xMerge(p, &doclist, &aBuf[i]);
            fts5BufferZero(&aBuf[i]);
          }
        }
        iLastRowid = 0;
      }

      xAppend(p, p1->base.iRowid-iLastRowid, p1, &doclist);
      iLastRowid = p1->base.iRowid;
    }

    for(i=0; i<nBuf; i++){
      if( p->rc==SQLITE_OK ){
        xMerge(p, &doclist, &aBuf[i]);
      }
      fts5BufferFree(&aBuf[i]);
    }
    fts5MultiIterFree(p1);

    pData = fts5IdxMalloc(p, sizeof(Fts5Data)+doclist.n+FTS5_DATA_ZERO_PADDING);
    if( pData ){
      pData->p = (u8*)&pData[1];
      pData->nn = pData->szLeaf = doclist.n;
      if( doclist.n ) memcpy(pData->p, doclist.p, doclist.n);
      fts5MultiIterNew2(p, pData, bDesc, ppIter);
    }
    fts5BufferFree(&doclist);
  }

  fts5StructureRelease(pStruct);
  sqlite3_free(aBuf);
}