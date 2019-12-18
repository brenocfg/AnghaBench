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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ nUsed; scalar_t__ nAlloc; scalar_t__ zBuf; } ;
typedef  TYPE_1__ JsonString ;

/* Variables and functions */
 scalar_t__ jsonGrow (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,scalar_t__) ; 

__attribute__((used)) static void jsonAppendRaw(JsonString *p, const char *zIn, u32 N){
  if( (N+p->nUsed >= p->nAlloc) && jsonGrow(p,N)!=0 ) return;
  memcpy(p->zBuf+p->nUsed, zIn, N);
  p->nUsed += N;
}