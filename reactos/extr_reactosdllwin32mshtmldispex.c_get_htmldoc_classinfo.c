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
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_HTMLDocument ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITypeLib_GetTypeInfoOfGuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  load_typelib () ; 
 int /*<<< orphan*/  typelib ; 

HRESULT get_htmldoc_classinfo(ITypeInfo **typeinfo)
{
    HRESULT hres;

    if (!typelib)
        hres = load_typelib();
    if (!typelib)
        return hres;

    hres = ITypeLib_GetTypeInfoOfGuid(typelib, &CLSID_HTMLDocument, typeinfo);
    if(FAILED(hres))
        ERR("GetTypeInfoOfGuid failed: %08x\n", hres);
    return hres;
}