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
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  int /*<<< orphan*/  IAssemblyNameImpl ;
typedef  TYPE_1__ IAssemblyName ;

/* Variables and functions */
 int /*<<< orphan*/  AssemblyNameVtbl ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * impl_from_IAssemblyName (TYPE_1__*) ; 

__attribute__((used)) static inline IAssemblyNameImpl *unsafe_impl_from_IAssemblyName(IAssemblyName *iface)
{
    assert(iface->lpVtbl == &AssemblyNameVtbl);

    return impl_from_IAssemblyName(iface);
}