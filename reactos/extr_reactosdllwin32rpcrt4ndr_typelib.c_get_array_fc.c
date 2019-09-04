#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ typekind; } ;
struct TYPE_7__ {scalar_t__ vt; int /*<<< orphan*/  hreftype; } ;
typedef  TYPE_1__ TYPEDESC ;
typedef  TYPE_2__ TYPEATTR ;
typedef  int /*<<< orphan*/  ITypeInfo ;

/* Variables and functions */
 unsigned char FC_BOGUS_ARRAY ; 
 unsigned char FC_LGFARRAY ; 
 scalar_t__ FC_STRUCT ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ TKIND_ENUM ; 
 scalar_t__ TKIND_RECORD ; 
 scalar_t__ VT_USERDEFINED ; 
 scalar_t__ get_base_type (scalar_t__) ; 
 scalar_t__ get_struct_fc (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static unsigned char get_array_fc(ITypeInfo *typeinfo, TYPEDESC *desc)
{
    if (get_base_type(desc->vt))
        return FC_LGFARRAY;
    else if (desc->vt == VT_USERDEFINED)
    {
        ITypeInfo *refinfo;
        TYPEATTR *attr;
        unsigned char fc;

        ITypeInfo_GetRefTypeInfo(typeinfo, desc->hreftype, &refinfo);
        ITypeInfo_GetTypeAttr(refinfo, &attr);

        if (attr->typekind == TKIND_ENUM)
            fc = FC_LGFARRAY;
        else if (attr->typekind == TKIND_RECORD && get_struct_fc(refinfo, attr) == FC_STRUCT)
            fc = FC_LGFARRAY;
        else
            fc = FC_BOGUS_ARRAY;

        ITypeInfo_ReleaseTypeAttr(refinfo, attr);
        ITypeInfo_Release(refinfo);

        return fc;
    }
    else
        return FC_BOGUS_ARRAY;
}