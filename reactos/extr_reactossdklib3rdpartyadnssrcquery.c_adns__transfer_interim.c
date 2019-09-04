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
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  allocnode ;
typedef  TYPE_1__* adns_query ;
struct TYPE_4__ {size_t interim_allocd; scalar_t__ expires; int /*<<< orphan*/  allocations; int /*<<< orphan*/  final_allocspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_LINK_TAIL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_UNLINK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MEM_ROUND (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 

void adns__transfer_interim(adns_query from, adns_query to, void *block, size_t sz) {
  allocnode *an;

  if (!block) return;
  an= (void*)((byte*)block - MEM_ROUND(sizeof(*an)));

  assert(!to->final_allocspace);
  assert(!from->final_allocspace);

  LIST_UNLINK(from->allocations,an);
  LIST_LINK_TAIL(to->allocations,an);

  sz= MEM_ROUND(sz);
  from->interim_allocd -= sz;
  to->interim_allocd += sz;

  if (to->expires > from->expires) to->expires= from->expires;
}