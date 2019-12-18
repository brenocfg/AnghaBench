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
typedef  int /*<<< orphan*/  vlc_va_t ;
struct va_pool_cfg {scalar_t__ (* pf_create_device ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  poolrefs; scalar_t__ surface_count; struct va_pool_cfg callbacks; } ;
typedef  TYPE_1__ va_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

va_pool_t * va_pool_Create(vlc_va_t *va, const struct va_pool_cfg *cbs)
{
    va_pool_t *va_pool = malloc(sizeof(*va_pool));
    if (unlikely(va_pool == NULL))
        return NULL;

    va_pool->callbacks = *cbs;

    /* */
    if (cbs->pf_create_device(va)) {
        msg_Err(va, "Failed to create device");
        return NULL;
    }
    msg_Dbg(va, "CreateDevice succeed");

    va_pool->surface_count = 0;
    atomic_init(&va_pool->poolrefs, 1);

    return va_pool;
}