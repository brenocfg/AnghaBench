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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ n; scalar_t__ nAlloc; int errNoMem; scalar_t__ a; } ;
typedef  TYPE_1__ lsm1_vblob ;

/* Variables and functions */
 scalar_t__ sqlite3_msize (scalar_t__) ; 
 scalar_t__ sqlite3_realloc64 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int lsm1VblobEnlarge(lsm1_vblob *p, u32 N){
  if( p->n+N>p->nAlloc ){
    if( p->errNoMem ) return 1;
    p->nAlloc += N + (p->nAlloc ? p->nAlloc : N);
    p->a = sqlite3_realloc64(p->a, p->nAlloc);
    if( p->a==0 ){
      p->n = 0;
      p->nAlloc = 0;
      p->errNoMem = 1;
      return 1;
    }
    p->nAlloc = sqlite3_msize(p->a);
  }
  return 0;
}