#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  nData; int /*<<< orphan*/  pData; } ;
struct TYPE_9__ {int flags; int eType; TYPE_1__ key; int /*<<< orphan*/ * aTree; } ;
typedef  TYPE_2__ MultiCursor ;

/* Variables and functions */
 int CURSOR_IGNORE_DELETE ; 
 int LSM_OK ; 
 int LSM_SYSTEMKEY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mcursorLocationOk (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiCursorCacheKey (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  multiCursorGetKey (TYPE_2__*,int /*<<< orphan*/ ,int*,void**,int*) ; 
 int sortedDbKeyCompare (TYPE_2__*,int,void*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcursorAdvanceOk(
  MultiCursor *pCsr, 
  int bReverse,
  int *pRc
){
  void *pNew;                     /* Pointer to buffer containing new key */
  int nNew;                       /* Size of buffer pNew in bytes */
  int eNewType;                   /* Type of new record */

  if( *pRc ) return 1;

  /* Check the current key value. If it is not greater than (if bReverse==0)
  ** or less than (if bReverse!=0) the key currently cached in pCsr->key, 
  ** then the cursor has not yet been successfully advanced.  
  */
  multiCursorGetKey(pCsr, pCsr->aTree[1], &eNewType, &pNew, &nNew);
  if( pNew ){
    int typemask = (pCsr->flags & CURSOR_IGNORE_DELETE) ? ~(0) : LSM_SYSTEMKEY;
    int res = sortedDbKeyCompare(pCsr,
      eNewType & typemask, pNew, nNew, 
      pCsr->eType & typemask, pCsr->key.pData, pCsr->key.nData
    );

    if( (bReverse==0 && res<=0) || (bReverse!=0 && res>=0) ){
      return 0;
    }

    multiCursorCacheKey(pCsr, pRc);
    assert( pCsr->eType==eNewType );

    /* If this cursor is configured to skip deleted keys, and the current
    ** cursor points to a SORTED_DELETE entry, then the cursor has not been 
    ** successfully advanced.  
    **
    ** Similarly, if the cursor is configured to skip system keys and the
    ** current cursor points to a system key, it has not yet been advanced.
    */
    if( *pRc==LSM_OK && 0==mcursorLocationOk(pCsr, 0) ) return 0;
  }
  return 1;
}