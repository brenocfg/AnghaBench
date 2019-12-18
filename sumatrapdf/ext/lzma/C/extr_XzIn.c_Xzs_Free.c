#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t num; size_t numAllocated; int /*<<< orphan*/ * streams; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* Free ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ ISzAlloc ;
typedef  TYPE_2__ CXzs ;

/* Variables and functions */
 int /*<<< orphan*/  Xz_Free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

void Xzs_Free(CXzs *p, ISzAlloc *alloc)
{
  size_t i;
  for (i = 0; i < p->num; i++)
    Xz_Free(&p->streams[i], alloc);
  alloc->Free(alloc, p->streams);
  p->num = p->numAllocated = 0;
  p->streams = 0;
}