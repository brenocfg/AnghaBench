#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* adns_query ;
struct TYPE_8__ {int /*<<< orphan*/  preserved_allocd; int /*<<< orphan*/  interim_allocd; TYPE_2__* answer; int /*<<< orphan*/  final_allocspace; } ;
struct TYPE_6__ {scalar_t__ untyped; } ;
struct TYPE_7__ {TYPE_1__ rrs; scalar_t__ nrrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cancel_children (TYPE_3__*) ; 

void adns__reset_preserved(adns_query qu) {
  assert(!qu->final_allocspace);
  cancel_children(qu);
  qu->answer->nrrs= 0;
  qu->answer->rrs.untyped= 0;
  qu->interim_allocd= qu->preserved_allocd;
}