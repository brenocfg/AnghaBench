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
typedef  size_t u8 ;
struct TYPE_8__ {TYPE_2__* pSorter; } ;
struct TYPE_7__ {TYPE_1__* pKeyInfo; } ;
struct TYPE_6__ {int nKeyField; scalar_t__* aSortOrder; } ;
typedef  TYPE_3__ SortSubtask ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int vdbeSorterCompareTail (TYPE_3__*,int*,void const*,int,void const*,int) ; 

__attribute__((used)) static int vdbeSorterCompareInt(
  SortSubtask *pTask,             /* Subtask context (for pKeyInfo) */
  int *pbKey2Cached,              /* True if pTask->pUnpacked is pKey2 */
  const void *pKey1, int nKey1,   /* Left side of comparison */
  const void *pKey2, int nKey2    /* Right side of comparison */
){
  const u8 * const p1 = (const u8 * const)pKey1;
  const u8 * const p2 = (const u8 * const)pKey2;
  const int s1 = p1[1];                 /* Left hand serial type */
  const int s2 = p2[1];                 /* Right hand serial type */
  const u8 * const v1 = &p1[ p1[0] ];   /* Pointer to value 1 */
  const u8 * const v2 = &p2[ p2[0] ];   /* Pointer to value 2 */
  int res;                              /* Return value */

  assert( (s1>0 && s1<7) || s1==8 || s1==9 );
  assert( (s2>0 && s2<7) || s2==8 || s2==9 );

  if( s1==s2 ){
    /* The two values have the same sign. Compare using memcmp(). */
    static const u8 aLen[] = {0, 1, 2, 3, 4, 6, 8, 0, 0, 0 };
    const u8 n = aLen[s1];
    int i;
    res = 0;
    for(i=0; i<n; i++){
      if( (res = v1[i] - v2[i])!=0 ){
        if( ((v1[0] ^ v2[0]) & 0x80)!=0 ){
          res = v1[0] & 0x80 ? -1 : +1;
        }
        break;
      }
    }
  }else if( s1>7 && s2>7 ){
    res = s1 - s2;
  }else{
    if( s2>7 ){
      res = +1;
    }else if( s1>7 ){
      res = -1;
    }else{
      res = s1 - s2;
    }
    assert( res!=0 );

    if( res>0 ){
      if( *v1 & 0x80 ) res = -1;
    }else{
      if( *v2 & 0x80 ) res = +1;
    }
  }

  if( res==0 ){
    if( pTask->pSorter->pKeyInfo->nKeyField>1 ){
      res = vdbeSorterCompareTail(
          pTask, pbKey2Cached, pKey1, nKey1, pKey2, nKey2
      );
    }
  }else if( pTask->pSorter->pKeyInfo->aSortOrder[0] ){
    res = res * -1;
  }

  return res;
}