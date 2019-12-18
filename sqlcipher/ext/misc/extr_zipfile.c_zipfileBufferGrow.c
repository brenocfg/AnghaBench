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
typedef  int sqlite3_int64 ;
struct TYPE_3__ {int n; int nAlloc; int /*<<< orphan*/ * a; } ;
typedef  TYPE_1__ ZipfileBuffer ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/ * sqlite3_realloc64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int zipfileBufferGrow(ZipfileBuffer *pBuf, int nByte){
  if( pBuf->n+nByte>pBuf->nAlloc ){
    u8 *aNew;
    sqlite3_int64 nNew = pBuf->n ? pBuf->n*2 : 512;
    int nReq = pBuf->n + nByte;

    while( nNew<nReq ) nNew = nNew*2;
    aNew = sqlite3_realloc64(pBuf->a, nNew);
    if( aNew==0 ) return SQLITE_NOMEM;
    pBuf->a = aNew;
    pBuf->nAlloc = (int)nNew;
  }
  return SQLITE_OK;
}