#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct foldercollection {int /*<<< orphan*/  IFolderCollection_iface; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {struct foldercollection* coll; int /*<<< orphan*/ * find; } ;
struct TYPE_6__ {TYPE_1__ foldercoll; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct enumvariant {int ref; TYPE_4__ IEnumVARIANT_iface; TYPE_3__ data; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IFolderCollection_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  foldercollenumvariantvtbl ; 
 struct enumvariant* heap_alloc (int) ; 

__attribute__((used)) static HRESULT create_foldercoll_enum(struct foldercollection *collection, IUnknown **newenum)
{
    struct enumvariant *This;

    *newenum = NULL;

    This = heap_alloc(sizeof(*This));
    if (!This) return E_OUTOFMEMORY;

    This->IEnumVARIANT_iface.lpVtbl = &foldercollenumvariantvtbl;
    This->ref = 1;
    This->data.u.foldercoll.find = NULL;
    This->data.u.foldercoll.coll = collection;
    IFolderCollection_AddRef(&collection->IFolderCollection_iface);

    *newenum = (IUnknown*)&This->IEnumVARIANT_iface;

    return S_OK;
}