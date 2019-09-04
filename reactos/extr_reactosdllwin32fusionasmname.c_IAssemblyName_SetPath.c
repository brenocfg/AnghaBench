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
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ IAssemblyNameImpl ;
typedef  int /*<<< orphan*/  IAssemblyName ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  strdupW (int /*<<< orphan*/ ) ; 
 TYPE_1__* unsafe_impl_from_IAssemblyName (int /*<<< orphan*/ *) ; 

HRESULT IAssemblyName_SetPath(IAssemblyName *iface, LPCWSTR path)
{
    IAssemblyNameImpl *name = unsafe_impl_from_IAssemblyName(iface);

    name->path = strdupW(path);
    if (!name->path)
        return E_OUTOFMEMORY;

    return S_OK;
}