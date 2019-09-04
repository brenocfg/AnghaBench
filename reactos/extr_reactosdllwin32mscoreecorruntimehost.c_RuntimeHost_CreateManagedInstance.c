#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* mono; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* mono_runtime_object_init ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* mono_object_new ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* mono_class_from_mono_type ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* mono_reflection_type_from_name ) (char*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* mono_thread_attach ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ RuntimeHost ;
typedef  int /*<<< orphan*/  MonoType ;
typedef  int /*<<< orphan*/  MonoObject ;
typedef  int /*<<< orphan*/  MonoDomain ;
typedef  int /*<<< orphan*/  MonoClass ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RuntimeHost_GetDefaultDomain (TYPE_2__*,int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 char* WtoA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *) ; 

HRESULT RuntimeHost_CreateManagedInstance(RuntimeHost *This, LPCWSTR name,
    MonoDomain *domain, MonoObject **result)
{
    HRESULT hr=S_OK;
    char *nameA=NULL;
    MonoType *type;
    MonoClass *klass;
    MonoObject *obj;

    if (!domain)
        hr = RuntimeHost_GetDefaultDomain(This, &domain);

    if (SUCCEEDED(hr))
    {
        nameA = WtoA(name);
        if (!nameA)
            hr = E_OUTOFMEMORY;
    }

    if (SUCCEEDED(hr))
    {
        This->mono->mono_thread_attach(domain);

        type = This->mono->mono_reflection_type_from_name(nameA, NULL);
        if (!type)
        {
            ERR("Cannot find type %s\n", debugstr_w(name));
            hr = E_FAIL;
        }
    }

    if (SUCCEEDED(hr))
    {
        klass = This->mono->mono_class_from_mono_type(type);
        if (!klass)
        {
            ERR("Cannot convert type %s to a class\n", debugstr_w(name));
            hr = E_FAIL;
        }
    }

    if (SUCCEEDED(hr))
    {
        obj = This->mono->mono_object_new(domain, klass);
        if (!obj)
        {
            ERR("Cannot allocate object of type %s\n", debugstr_w(name));
            hr = E_FAIL;
        }
    }

    if (SUCCEEDED(hr))
    {
        /* FIXME: Detect exceptions from the constructor? */
        This->mono->mono_runtime_object_init(obj);
        *result = obj;
    }

    HeapFree(GetProcessHeap(), 0, nameA);

    return hr;
}