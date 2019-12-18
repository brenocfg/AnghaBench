#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void spl_kmem_obj_t ;
struct TYPE_3__ {int /*<<< orphan*/  skc_obj_align; int /*<<< orphan*/  skc_obj_size; } ;
typedef  TYPE_1__ spl_kmem_cache_t ;

/* Variables and functions */
 int P2ROUNDUP_TYPED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint32_t ; 

__attribute__((used)) static inline spl_kmem_obj_t *
spl_sko_from_obj(spl_kmem_cache_t *skc, void *obj)
{
	return (obj + P2ROUNDUP_TYPED(skc->skc_obj_size,
	    skc->skc_obj_align, uint32_t));
}