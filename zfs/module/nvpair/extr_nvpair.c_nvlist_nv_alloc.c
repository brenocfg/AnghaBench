#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  nv_alloc_t ;

/* Variables and functions */
#define  KM_PUSHPAGE 129 
#define  KM_SLEEP 128 
 int /*<<< orphan*/ * nv_alloc_nosleep ; 
 int /*<<< orphan*/ * nv_alloc_pushpage ; 
 int /*<<< orphan*/ * nv_alloc_sleep ; 

__attribute__((used)) static nv_alloc_t *
nvlist_nv_alloc(int kmflag)
{
#if defined(_KERNEL)
	switch (kmflag) {
	case KM_SLEEP:
		return (nv_alloc_sleep);
	case KM_PUSHPAGE:
		return (nv_alloc_pushpage);
	default:
		return (nv_alloc_nosleep);
	}
#else
	return (nv_alloc_nosleep);
#endif /* _KERNEL */
}