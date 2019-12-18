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
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IUnknown ;

/* Variables and functions */
 scalar_t__ IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LONG get_refcount(void *iface)
{
    IUnknown *unk = iface;
    LONG ref;

    ref = IUnknown_AddRef(unk);
    IUnknown_Release(unk);
    return ref-1;
}