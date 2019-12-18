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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_4__ {scalar_t__ n; scalar_t__ nAlloc; scalar_t__ a; } ;
typedef  TYPE_1__ lsm1_vblob ;

/* Variables and functions */
 int /*<<< orphan*/  lsm1VblobEnlargeAndAppend (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static void lsm1VblobAppend(lsm1_vblob *p, const u8 *pData, u32 N){
  sqlite3_int64 n = p->n;
  if( n+N>p->nAlloc ){
    lsm1VblobEnlargeAndAppend(p, pData, N);
  }else{
    p->n += N;
    memcpy(p->a+n, pData, N);
  }
}