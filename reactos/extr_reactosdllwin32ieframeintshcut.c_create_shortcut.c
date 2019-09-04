#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int refCount; int /*<<< orphan*/  property_set_storage; TYPE_4__ IPropertySetStorage_iface; TYPE_3__ IPersistFile_iface; TYPE_2__ IUniformResourceLocatorW_iface; TYPE_1__ IUniformResourceLocatorA_iface; } ;
typedef  TYPE_5__ InternetShortcut ;
typedef  int /*<<< orphan*/  IPropertyStorage ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMTID_Intshcut ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_5__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IID_IPropertySetStorage ; 
 int /*<<< orphan*/  IPropertySetStorage_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPropertySetStorage_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPropertyStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROPSETFLAG_DEFAULT ; 
 int /*<<< orphan*/  STGFMT_STORAGE ; 
 int STGM_CREATE ; 
 int STGM_DELETEONRELEASE ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 int /*<<< orphan*/  StgCreateStorageEx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  heap_free (TYPE_5__*) ; 
 int /*<<< orphan*/  persistFileVtbl ; 
 int /*<<< orphan*/  propertySetStorageVtbl ; 
 int /*<<< orphan*/  uniformResourceLocatorAVtbl ; 
 int /*<<< orphan*/  uniformResourceLocatorWVtbl ; 

__attribute__((used)) static InternetShortcut *create_shortcut(void)
{
    InternetShortcut *newshortcut;

    newshortcut = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(InternetShortcut));
    if (newshortcut)
    {
        HRESULT hr;
        IPropertyStorage *dummy;

        newshortcut->IUniformResourceLocatorA_iface.lpVtbl = &uniformResourceLocatorAVtbl;
        newshortcut->IUniformResourceLocatorW_iface.lpVtbl = &uniformResourceLocatorWVtbl;
        newshortcut->IPersistFile_iface.lpVtbl = &persistFileVtbl;
        newshortcut->IPropertySetStorage_iface.lpVtbl = &propertySetStorageVtbl;
        newshortcut->refCount = 1;
        hr = StgCreateStorageEx(NULL, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DELETEONRELEASE,
                                STGFMT_STORAGE, 0, NULL, NULL, &IID_IPropertySetStorage, (void **) &newshortcut->property_set_storage);
        if (FAILED(hr))
        {
            TRACE("Failed to create the storage object needed for the shortcut.\n");
            heap_free(newshortcut);
            return NULL;
        }

        hr = IPropertySetStorage_Create(newshortcut->property_set_storage, &FMTID_Intshcut, NULL, PROPSETFLAG_DEFAULT, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &dummy);
        if (FAILED(hr))
        {
            TRACE("Failed to create the property object needed for the shortcut.\n");
            IPropertySetStorage_Release(newshortcut->property_set_storage);
            heap_free(newshortcut);
            return NULL;
        }
        IPropertyStorage_Release(dummy);
    }

    return newshortcut;
}