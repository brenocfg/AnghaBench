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
struct TYPE_4__ {int /*<<< orphan*/  btSync; int /*<<< orphan*/  hashSync; } ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  TYPE_1__ CMatchFinderMt ;

/* Variables and functions */
 int /*<<< orphan*/  MatchFinderMt_FreeMem (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MtSync_Destruct (int /*<<< orphan*/ *) ; 

void MatchFinderMt_Destruct(CMatchFinderMt *p, ISzAlloc *alloc)
{
  MtSync_Destruct(&p->hashSync);
  MtSync_Destruct(&p->btSync);
  MatchFinderMt_FreeMem(p, alloc);
}