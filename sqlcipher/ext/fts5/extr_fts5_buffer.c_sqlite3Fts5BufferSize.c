#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int nSpace; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ Fts5Buffer ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int /*<<< orphan*/ * sqlite3_realloc64 (int /*<<< orphan*/ *,scalar_t__) ; 

int sqlite3Fts5BufferSize(int *pRc, Fts5Buffer *pBuf, u32 nByte){
  if( (u32)pBuf->nSpace<nByte ){
    u64 nNew = pBuf->nSpace ? pBuf->nSpace : 64;
    u8 *pNew;
    while( nNew<nByte ){
      nNew = nNew * 2;
    }
    pNew = sqlite3_realloc64(pBuf->p, nNew);
    if( pNew==0 ){
      *pRc = SQLITE_NOMEM;
      return 1;
    }else{
      pBuf->nSpace = (int)nNew;
      pBuf->p = pNew;
    }
  }
  return 0;
}