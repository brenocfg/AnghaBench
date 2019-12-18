#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  nData; int /*<<< orphan*/  pData; } ;
struct TYPE_8__ {int* aTree; int flags; int nPtr; int eType; TYPE_2__ key; TYPE_1__* pDb; } ;
struct TYPE_6__ {int /*<<< orphan*/  xCmp; } ;
typedef  TYPE_3__ MultiCursor ;

/* Variables and functions */
 int CURSOR_DATA_SEGMENT ; 
 int CURSOR_IGNORE_DELETE ; 
 int CURSOR_NEXT_OK ; 
 int LSM_END_DELETE ; 
 int LSM_INSERT ; 
 int LSM_POINT_DELETE ; 
 int LSM_START_DELETE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  multiCursorGetKey (TYPE_3__*,int,int*,void**,int*) ; 
 int /*<<< orphan*/  rtTopic (int) ; 
 int sortedKeyCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void mergeRangeDeletes(MultiCursor *pCsr, int *piVal, int *piFlags){
  int f = *piFlags;
  int iKey = pCsr->aTree[1];
  int i;

  assert( pCsr->flags & CURSOR_NEXT_OK );
  if( pCsr->flags & CURSOR_IGNORE_DELETE ){
    /* The ignore-delete flag is set when the output of the merge will form
    ** the oldest level in the database. In this case there is no point in
    ** retaining any range-delete flags.  */
    assert( (f & LSM_POINT_DELETE)==0 );
    f &= ~(LSM_START_DELETE|LSM_END_DELETE);
  }else{
    for(i=0; i<(CURSOR_DATA_SEGMENT + pCsr->nPtr); i++){
      if( i!=iKey ){
        int eType;
        void *pKey;
        int nKey;
        int res;
        multiCursorGetKey(pCsr, i, &eType, &pKey, &nKey);

        if( pKey ){
          res = sortedKeyCompare(pCsr->pDb->xCmp, 
              rtTopic(pCsr->eType), pCsr->key.pData, pCsr->key.nData,
              rtTopic(eType), pKey, nKey
          );
          assert( res<=0 );
          if( res==0 ){
            if( (f & (LSM_INSERT|LSM_POINT_DELETE))==0 ){
              if( eType & LSM_INSERT ){
                f |= LSM_INSERT;
                *piVal = i;
              }
              else if( eType & LSM_POINT_DELETE ){
                f |= LSM_POINT_DELETE;
              }
            }
            f |= (eType & (LSM_END_DELETE|LSM_START_DELETE));
          }

          if( i>iKey && (eType & LSM_END_DELETE) && res<0 ){
            if( f & (LSM_INSERT|LSM_POINT_DELETE) ){
              f |= (LSM_END_DELETE|LSM_START_DELETE);
            }else{
              f = 0;
            }
            break;
          }
        }
      }
    }

    assert( (f & LSM_INSERT)==0 || (f & LSM_POINT_DELETE)==0 );
    if( (f & LSM_START_DELETE) 
     && (f & LSM_END_DELETE) 
     && (f & LSM_POINT_DELETE )
    ){
      f = 0;
    }
  }

  *piFlags = f;
}