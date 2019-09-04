#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* propid_to_prop; void* propid_to_name; void* name_to_propid; } ;
typedef  TYPE_1__ PropertyStorage_impl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PropertyStorage_DestroyDictionaries (TYPE_1__*) ; 
 int /*<<< orphan*/  PropertyStorage_PropCompare ; 
 int /*<<< orphan*/  PropertyStorage_PropNameCompare ; 
 int /*<<< orphan*/ * PropertyStorage_PropNameDestroy ; 
 int /*<<< orphan*/ * PropertyStorage_PropertyDestroy ; 
 int /*<<< orphan*/  STG_E_INSUFFICIENTMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 void* dictionary_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static HRESULT PropertyStorage_CreateDictionaries(PropertyStorage_impl *This)
{
    HRESULT hr = S_OK;

    This->name_to_propid = dictionary_create(
     PropertyStorage_PropNameCompare, PropertyStorage_PropNameDestroy,
     This);
    if (!This->name_to_propid)
    {
        hr = STG_E_INSUFFICIENTMEMORY;
        goto end;
    }
    This->propid_to_name = dictionary_create(PropertyStorage_PropCompare,
     NULL, This);
    if (!This->propid_to_name)
    {
        hr = STG_E_INSUFFICIENTMEMORY;
        goto end;
    }
    This->propid_to_prop = dictionary_create(PropertyStorage_PropCompare,
     PropertyStorage_PropertyDestroy, This);
    if (!This->propid_to_prop)
    {
        hr = STG_E_INSUFFICIENTMEMORY;
        goto end;
    }
end:
    if (FAILED(hr))
        PropertyStorage_DestroyDictionaries(This);
    return hr;
}