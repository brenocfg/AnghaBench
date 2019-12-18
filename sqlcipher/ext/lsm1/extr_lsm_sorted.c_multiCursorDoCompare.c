#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* aTree; int nTree; } ;
typedef  TYPE_1__ MultiCursor ;

/* Variables and functions */
 int LSM_INSERT ; 
 int LSM_POINT_DELETE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiCursorGetKey (TYPE_1__*,int,int*,void**,int*) ; 
 int sortedDbKeyCompare (TYPE_1__*,int,void*,int,int,void*,int) ; 

__attribute__((used)) static void multiCursorDoCompare(MultiCursor *pCsr, int iOut, int bReverse){
  int i1;
  int i2;
  int iRes;
  void *pKey1; int nKey1; int eType1;
  void *pKey2; int nKey2; int eType2;
  const int mul = (bReverse ? -1 : 1);

  assert( pCsr->aTree && iOut<pCsr->nTree );
  if( iOut>=(pCsr->nTree/2) ){
    i1 = (iOut - pCsr->nTree/2) * 2;
    i2 = i1 + 1;
  }else{
    i1 = pCsr->aTree[iOut*2];
    i2 = pCsr->aTree[iOut*2+1];
  }

  multiCursorGetKey(pCsr, i1, &eType1, &pKey1, &nKey1);
  multiCursorGetKey(pCsr, i2, &eType2, &pKey2, &nKey2);

  if( pKey1==0 ){
    iRes = i2;
  }else if( pKey2==0 ){
    iRes = i1;
  }else{
    int res;

    /* Compare the keys */
    res = sortedDbKeyCompare(pCsr,
        eType1, pKey1, nKey1, eType2, pKey2, nKey2
    );

    res = res * mul;
    if( res==0 ){
      /* The two keys are identical. Normally, this means that the key from
      ** the newer run clobbers the old. However, if the newer key is a
      ** separator key, or a range-delete-boundary only, do not allow it
      ** to clobber an older entry.  */
      int nc1 = (eType1 & (LSM_INSERT|LSM_POINT_DELETE))==0;
      int nc2 = (eType2 & (LSM_INSERT|LSM_POINT_DELETE))==0;
      iRes = (nc1 > nc2) ? i2 : i1;
    }else if( res<0 ){
      iRes = i1;
    }else{
      iRes = i2;
    }
  }

  pCsr->aTree[iOut] = iRes;
}