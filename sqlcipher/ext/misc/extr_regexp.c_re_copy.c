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
struct TYPE_4__ {int nState; int nAlloc; int /*<<< orphan*/ * aArg; int /*<<< orphan*/ * aOp; } ;
typedef  TYPE_1__ ReCompiled ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ re_resize (TYPE_1__*,int) ; 

__attribute__((used)) static void re_copy(ReCompiled *p, int iStart, int N){
  if( p->nState+N>=p->nAlloc && re_resize(p, p->nAlloc*2+N) ) return;
  memcpy(&p->aOp[p->nState], &p->aOp[iStart], N*sizeof(p->aOp[0]));
  memcpy(&p->aArg[p->nState], &p->aArg[iStart], N*sizeof(p->aArg[0]));
  p->nState += N;
}