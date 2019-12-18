#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {scalar_t__ eDetail; } ;
struct TYPE_6__ {int iSzPoslist; int nData; int bDel; scalar_t__ bContent; } ;
typedef  TYPE_1__ Fts5HashEntry ;
typedef  TYPE_2__ Fts5Hash ;

/* Variables and functions */
 scalar_t__ FTS5_DETAIL_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int sqlite3Fts5GetVarintLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Fts5PutVarint (int*,int) ; 

__attribute__((used)) static int fts5HashAddPoslistSize(
  Fts5Hash *pHash, 
  Fts5HashEntry *p,
  Fts5HashEntry *p2
){
  int nRet = 0;
  if( p->iSzPoslist ){
    u8 *pPtr = p2 ? (u8*)p2 : (u8*)p;
    int nData = p->nData;
    if( pHash->eDetail==FTS5_DETAIL_NONE ){
      assert( nData==p->iSzPoslist );
      if( p->bDel ){
        pPtr[nData++] = 0x00;
        if( p->bContent ){
          pPtr[nData++] = 0x00;
        }
      }
    }else{
      int nSz = (nData - p->iSzPoslist - 1);       /* Size in bytes */
      int nPos = nSz*2 + p->bDel;                     /* Value of nPos field */

      assert( p->bDel==0 || p->bDel==1 );
      if( nPos<=127 ){
        pPtr[p->iSzPoslist] = (u8)nPos;
      }else{
        int nByte = sqlite3Fts5GetVarintLen((u32)nPos);
        memmove(&pPtr[p->iSzPoslist + nByte], &pPtr[p->iSzPoslist + 1], nSz);
        sqlite3Fts5PutVarint(&pPtr[p->iSzPoslist], nPos);
        nData += (nByte-1);
      }
    }

    nRet = nData - p->nData;
    if( p2==0 ){
      p->iSzPoslist = 0;
      p->bDel = 0;
      p->bContent = 0;
      p->nData = nData;
    }
  }
  return nRet;
}