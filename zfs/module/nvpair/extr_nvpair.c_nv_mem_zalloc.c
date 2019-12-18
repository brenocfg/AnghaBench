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
struct TYPE_7__ {TYPE_3__* nvp_nva; } ;
typedef  TYPE_2__ nvpriv_t ;
struct TYPE_8__ {TYPE_1__* nva_ops; } ;
typedef  TYPE_3__ nv_alloc_t ;
struct TYPE_6__ {void* (* nv_ao_alloc ) (TYPE_3__*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 void* stub1 (TYPE_3__*,size_t) ; 

__attribute__((used)) static void *
nv_mem_zalloc(nvpriv_t *nvp, size_t size)
{
	nv_alloc_t *nva = nvp->nvp_nva;
	void *buf;

	if ((buf = nva->nva_ops->nv_ao_alloc(nva, size)) != NULL)
		bzero(buf, size);

	return (buf);
}