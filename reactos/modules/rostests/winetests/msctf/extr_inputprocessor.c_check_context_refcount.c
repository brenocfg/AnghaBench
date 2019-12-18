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
typedef  int /*<<< orphan*/  ITfContext ;

/* Variables and functions */
 int /*<<< orphan*/  ITfContext_AddRef (int /*<<< orphan*/ *) ; 
 int ITfContext_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int check_context_refcount(ITfContext *iface)
{
    ITfContext_AddRef(iface);
    return ITfContext_Release(iface);
}