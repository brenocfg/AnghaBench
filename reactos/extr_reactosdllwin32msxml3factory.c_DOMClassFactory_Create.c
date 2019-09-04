#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {TYPE_4__ IClassFactory_iface; int /*<<< orphan*/  pCreateInstance; int /*<<< orphan*/  version; scalar_t__ ref; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  DOMFactoryCreateInstanceFunc ;
typedef  TYPE_1__ DOMFactory ;

/* Variables and functions */
 int /*<<< orphan*/  DOMClassFactoryVtbl ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IClassFactory_QueryInterface (TYPE_4__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  get_msxml_version (int /*<<< orphan*/  const*) ; 
 TYPE_1__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static HRESULT DOMClassFactory_Create(const GUID *clsid, REFIID riid, void **ppv, DOMFactoryCreateInstanceFunc fnCreateInstance)
{
    DOMFactory *ret = heap_alloc(sizeof(DOMFactory));
    HRESULT hres;

    ret->IClassFactory_iface.lpVtbl = &DOMClassFactoryVtbl;
    ret->ref = 0;
    ret->version = get_msxml_version(clsid);
    ret->pCreateInstance = fnCreateInstance;

    hres = IClassFactory_QueryInterface(&ret->IClassFactory_iface, riid, ppv);
    if(FAILED(hres)) {
        heap_free(ret);
        *ppv = NULL;
    }
    return hres;
}