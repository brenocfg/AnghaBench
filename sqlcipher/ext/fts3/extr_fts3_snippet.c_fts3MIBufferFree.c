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
typedef  int u32 ;
struct TYPE_3__ {int* aMatchinfo; int nElem; scalar_t__* aRef; } ;
typedef  TYPE_1__ MatchinfoBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static void fts3MIBufferFree(void *p){
  MatchinfoBuffer *pBuf = (MatchinfoBuffer*)((u8*)p - ((u32*)p)[-1]);

  assert( (u32*)p==&pBuf->aMatchinfo[1] 
       || (u32*)p==&pBuf->aMatchinfo[pBuf->nElem+2] 
  );
  if( (u32*)p==&pBuf->aMatchinfo[1] ){
    pBuf->aRef[1] = 0;
  }else{
    pBuf->aRef[2] = 0;
  }

  if( pBuf->aRef[0]==0 && pBuf->aRef[1]==0 && pBuf->aRef[2]==0 ){
    sqlite3_free(pBuf);
  }
}