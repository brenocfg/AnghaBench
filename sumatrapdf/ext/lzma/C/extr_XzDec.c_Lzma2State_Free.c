#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* Free ) (TYPE_1__*,void*) ;} ;
typedef  TYPE_1__ ISzAlloc ;
typedef  int /*<<< orphan*/  CLzma2Dec ;

/* Variables and functions */
 int /*<<< orphan*/  Lzma2Dec_Free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*) ; 

__attribute__((used)) static void Lzma2State_Free(void *pp, ISzAlloc *alloc)
{
  Lzma2Dec_Free((CLzma2Dec *)pp, alloc);
  alloc->Free(alloc, pp);
}