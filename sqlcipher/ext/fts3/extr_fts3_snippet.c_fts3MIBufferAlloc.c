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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int* aRef; int nElem; int /*<<< orphan*/ * aMatchinfo; scalar_t__ bGlobal; } ;
typedef  TYPE_1__ MatchinfoBuffer ;

/* Variables and functions */
 void fts3MIBufferFree (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void sqlite3_free (void*) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 

__attribute__((used)) static void (*fts3MIBufferAlloc(MatchinfoBuffer *p, u32 **paOut))(void*){
  void (*xRet)(void*) = 0;
  u32 *aOut = 0;

  if( p->aRef[1]==0 ){
    p->aRef[1] = 1;
    aOut = &p->aMatchinfo[1];
    xRet = fts3MIBufferFree;
  }
  else if( p->aRef[2]==0 ){
    p->aRef[2] = 1;
    aOut = &p->aMatchinfo[p->nElem+2];
    xRet = fts3MIBufferFree;
  }else{
    aOut = (u32*)sqlite3_malloc64(p->nElem * sizeof(u32));
    if( aOut ){
      xRet = sqlite3_free;
      if( p->bGlobal ) memcpy(aOut, &p->aMatchinfo[1], p->nElem*sizeof(u32));
    }
  }

  *paOut = aOut;
  return xRet;
}