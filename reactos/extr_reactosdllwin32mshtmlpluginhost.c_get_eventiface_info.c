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
struct TYPE_4__ {scalar_t__ typekind; int cImplTypes; } ;
typedef  TYPE_1__ TYPEATTR ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  HTMLPluginContainer ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HREFTYPE ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int IMPLTYPEFLAG_FDEFAULT ; 
 int IMPLTYPEFLAG_FSOURCE ; 
 int /*<<< orphan*/  ITypeInfo_GetImplTypeFlags (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeOfImplType (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ TKIND_COCLASS ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static ITypeInfo *get_eventiface_info(HTMLPluginContainer *plugin_container, ITypeInfo *class_info)
{
    int impl_types, i, impl_flags;
    ITypeInfo *ret = NULL;
    TYPEATTR *typeattr;
    HREFTYPE ref;
    HRESULT hres;

    hres = ITypeInfo_GetTypeAttr(class_info, &typeattr);
    if(FAILED(hres))
        return NULL;

    if(typeattr->typekind != TKIND_COCLASS) {
        WARN("not coclass\n");
        ITypeInfo_ReleaseTypeAttr(class_info, typeattr);
        return NULL;
    }

    impl_types = typeattr->cImplTypes;
    ITypeInfo_ReleaseTypeAttr(class_info, typeattr);

    for(i=0; i<impl_types; i++) {
        hres = ITypeInfo_GetImplTypeFlags(class_info, i, &impl_flags);
        if(FAILED(hres))
            continue;

        if((impl_flags & IMPLTYPEFLAG_FSOURCE)) {
            if(!(impl_flags & IMPLTYPEFLAG_FDEFAULT)) {
                FIXME("Handle non-default source iface\n");
                continue;
            }

            hres = ITypeInfo_GetRefTypeOfImplType(class_info, i, &ref);
            if(FAILED(hres))
                continue;

            hres = ITypeInfo_GetRefTypeInfo(class_info, ref, &ret);
            if(FAILED(hres))
                ret = NULL;
        }
    }

    return ret;
}