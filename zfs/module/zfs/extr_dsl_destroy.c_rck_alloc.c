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
struct TYPE_4__ {int /*<<< orphan*/ * rck_clone; } ;
typedef  TYPE_1__ remaining_clones_key_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static remaining_clones_key_t *
rck_alloc(dsl_dataset_t *clone)
{
	remaining_clones_key_t *rck = kmem_alloc(sizeof (*rck), KM_SLEEP);
	rck->rck_clone = clone;
	return (rck);
}