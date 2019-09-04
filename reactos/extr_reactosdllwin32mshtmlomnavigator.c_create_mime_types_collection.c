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
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_1__ IHTMLMimeTypesCollection_iface; int /*<<< orphan*/  dispex; int /*<<< orphan*/ * navigator; } ;
typedef  int /*<<< orphan*/  OmNavigator ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_2__ HTMLMimeTypesCollection ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLMimeTypesCollectionVtbl ; 
 int /*<<< orphan*/  HTMLMimeTypesCollection_dispex ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_mime_types_collection(OmNavigator *navigator, HTMLMimeTypesCollection **ret)
{
    HTMLMimeTypesCollection *col;

    col = heap_alloc_zero(sizeof(*col));
    if(!col)
        return E_OUTOFMEMORY;

    col->IHTMLMimeTypesCollection_iface.lpVtbl = &HTMLMimeTypesCollectionVtbl;
    col->ref = 1;
    col->navigator = navigator;

    init_dispex(&col->dispex, (IUnknown*)&col->IHTMLMimeTypesCollection_iface,
                &HTMLMimeTypesCollection_dispex);

    *ret = col;
    return S_OK;
}