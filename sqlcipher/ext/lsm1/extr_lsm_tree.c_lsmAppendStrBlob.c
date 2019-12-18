#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct TYPE_4__ {scalar_t__ nAlloc; char* z; size_t n; } ;
typedef  TYPE_1__ LsmString ;

/* Variables and functions */
 int /*<<< orphan*/  lsmStringExtend (TYPE_1__*,int) ; 

__attribute__((used)) static void lsmAppendStrBlob(LsmString *pStr, void *pBlob, int nBlob){
  int i;
  lsmStringExtend(pStr, nBlob*2);
  if( pStr->nAlloc==0 ) return;
  for(i=0; i<nBlob; i++){
    u8 c = ((u8*)pBlob)[i];
    if( c>='a' && c<='z' ){
      pStr->z[pStr->n++] = c;
    }else if( c!=0 || nBlob==1 || i!=(nBlob-1) ){
      pStr->z[pStr->n++] = "0123456789abcdef"[(c>>4)&0xf];
      pStr->z[pStr->n++] = "0123456789abcdef"[c&0xf];
    }
  }
  pStr->z[pStr->n] = 0;
}