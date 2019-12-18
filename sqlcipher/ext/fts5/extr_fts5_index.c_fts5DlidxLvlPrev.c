#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ i64 ;
struct TYPE_5__ {int iOff; int bEof; int iFirstOff; scalar_t__ iLeafPgno; int /*<<< orphan*/  iRowid; TYPE_1__* pData; } ;
struct TYPE_4__ {int* p; } ;
typedef  TYPE_2__ Fts5DlidxLvl ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5GetVarint (int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5DlidxLvlPrev(Fts5DlidxLvl *pLvl){
  int iOff = pLvl->iOff;

  assert( pLvl->bEof==0 );
  if( iOff<=pLvl->iFirstOff ){
    pLvl->bEof = 1;
  }else{
    u8 *a = pLvl->pData->p;
    i64 iVal;
    int iLimit;
    int ii;
    int nZero = 0;

    /* Currently iOff points to the first byte of a varint. This block 
    ** decrements iOff until it points to the first byte of the previous 
    ** varint. Taking care not to read any memory locations that occur
    ** before the buffer in memory.  */
    iLimit = (iOff>9 ? iOff-9 : 0);
    for(iOff--; iOff>iLimit; iOff--){
      if( (a[iOff-1] & 0x80)==0 ) break;
    }

    fts5GetVarint(&a[iOff], (u64*)&iVal);
    pLvl->iRowid -= iVal;
    pLvl->iLeafPgno--;

    /* Skip backwards past any 0x00 varints. */
    for(ii=iOff-1; ii>=pLvl->iFirstOff && a[ii]==0x00; ii--){
      nZero++;
    }
    if( ii>=pLvl->iFirstOff && (a[ii] & 0x80) ){
      /* The byte immediately before the last 0x00 byte has the 0x80 bit
      ** set. So the last 0x00 is only a varint 0 if there are 8 more 0x80
      ** bytes before a[ii]. */
      int bZero = 0;              /* True if last 0x00 counts */
      if( (ii-8)>=pLvl->iFirstOff ){
        int j;
        for(j=1; j<=8 && (a[ii-j] & 0x80); j++);
        bZero = (j>8);
      }
      if( bZero==0 ) nZero--;
    }
    pLvl->iLeafPgno -= nZero;
    pLvl->iOff = iOff - nZero;
  }

  return pLvl->bEof;
}