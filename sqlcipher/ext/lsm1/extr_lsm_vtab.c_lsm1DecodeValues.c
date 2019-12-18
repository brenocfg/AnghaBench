#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  void* u32 ;
typedef  int sqlite3_uint64 ;
struct TYPE_6__ {int nVal; } ;
typedef  TYPE_2__ lsm1_vtab ;
struct TYPE_5__ {scalar_t__ pVtab; } ;
struct TYPE_7__ {int nData; int* aiOfst; scalar_t__ zData; void** aiLen; scalar_t__* aeType; int /*<<< orphan*/  pLsmCur; TYPE_1__ base; } ;
typedef  TYPE_3__ lsm1_cursor ;

/* Variables and functions */
 scalar_t__ lsm1GetVarint64 (scalar_t__,int,int*) ; 
 int lsm_csr_value (int /*<<< orphan*/ ,void const**,int*) ; 

__attribute__((used)) static int lsm1DecodeValues(lsm1_cursor *pCur){
  lsm1_vtab *pTab = (lsm1_vtab*)(pCur->base.pVtab);
  int i, n;
  int rc;
  u8 eType;
  sqlite3_uint64 v;

  if( pCur->zData ) return 1;
  rc = lsm_csr_value(pCur->pLsmCur, (const void**)&pCur->zData,
                     (int*)&pCur->nData);
  if( rc ) return 0;
  for(i=n=0; i<pTab->nVal; i++){
    v = 0;
    n += lsm1GetVarint64(pCur->zData+n, pCur->nData-n, &v);
    pCur->aeType[i] = eType = (u8)(v%6);
    if( eType==0 ){
      pCur->aiOfst[i] = (u32)(v/6);
      pCur->aiLen[i] = 0;
    }else{ 
      pCur->aiOfst[i] = n;
      n += (pCur->aiLen[i] = (u32)(v/6));
    }
    if( n>pCur->nData ) break;
  }
  if( i<pTab->nVal ){
    pCur->zData = 0;
    return 0;
  }
  return 1;
}