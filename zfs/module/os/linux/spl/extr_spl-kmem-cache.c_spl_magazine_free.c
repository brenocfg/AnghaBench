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
struct TYPE_4__ {scalar_t__ skm_magic; scalar_t__ skm_avail; } ;
typedef  TYPE_1__ spl_kmem_magazine_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ SKM_MAGIC ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void
spl_magazine_free(spl_kmem_magazine_t *skm)
{
	ASSERT(skm->skm_magic == SKM_MAGIC);
	ASSERT(skm->skm_avail == 0);
	kfree(skm);
}