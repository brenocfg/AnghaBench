#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int sqlite3_int64 ;
struct TYPE_13__ {int mallocFailed; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_15__ {TYPE_1__* db; } ;
struct TYPE_14__ {int nSrc; scalar_t__ nAlloc; TYPE_11__* a; } ;
struct TYPE_12__ {int iCursor; } ;
typedef  TYPE_2__ SrcList ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int SQLITE_MAX_SRCLIST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* sqlite3DbRealloc (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_3__*,char*,int) ; 

SrcList *sqlite3SrcListEnlarge(
  Parse *pParse,     /* Parsing context into which errors are reported */
  SrcList *pSrc,     /* The SrcList to be enlarged */
  int nExtra,        /* Number of new slots to add to pSrc->a[] */
  int iStart         /* Index in pSrc->a[] of first new slot */
){
  int i;

  /* Sanity checking on calling parameters */
  assert( iStart>=0 );
  assert( nExtra>=1 );
  assert( pSrc!=0 );
  assert( iStart<=pSrc->nSrc );

  /* Allocate additional space if needed */
  if( (u32)pSrc->nSrc+nExtra>pSrc->nAlloc ){
    SrcList *pNew;
    sqlite3_int64 nAlloc = 2*(sqlite3_int64)pSrc->nSrc+nExtra;
    sqlite3 *db = pParse->db;

    if( pSrc->nSrc+nExtra>=SQLITE_MAX_SRCLIST ){
      sqlite3ErrorMsg(pParse, "too many FROM clause terms, max: %d",
                      SQLITE_MAX_SRCLIST);
      return 0;
    }
    if( nAlloc>SQLITE_MAX_SRCLIST ) nAlloc = SQLITE_MAX_SRCLIST;
    pNew = sqlite3DbRealloc(db, pSrc,
               sizeof(*pSrc) + (nAlloc-1)*sizeof(pSrc->a[0]) );
    if( pNew==0 ){
      assert( db->mallocFailed );
      return 0;
    }
    pSrc = pNew;
    pSrc->nAlloc = nAlloc;
  }

  /* Move existing slots that come after the newly inserted slots
  ** out of the way */
  for(i=pSrc->nSrc-1; i>=iStart; i--){
    pSrc->a[i+nExtra] = pSrc->a[i];
  }
  pSrc->nSrc += nExtra;

  /* Zero the newly allocated slots */
  memset(&pSrc->a[iStart], 0, sizeof(pSrc->a[0])*nExtra);
  for(i=iStart; i<iStart+nExtra; i++){
    pSrc->a[i].iCursor = -1;
  }

  /* Return a pointer to the enlarged SrcList */
  return pSrc;
}