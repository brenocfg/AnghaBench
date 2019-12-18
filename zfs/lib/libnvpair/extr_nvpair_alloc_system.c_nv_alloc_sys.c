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
struct TYPE_3__ {scalar_t__ nva_arg; } ;
typedef  TYPE_1__ nv_alloc_t ;

/* Variables and functions */
 void* kmem_alloc (size_t,int) ; 

__attribute__((used)) static void *
nv_alloc_sys(nv_alloc_t *nva, size_t size)
{
	return (kmem_alloc(size, (int)(uintptr_t)nva->nva_arg));
}