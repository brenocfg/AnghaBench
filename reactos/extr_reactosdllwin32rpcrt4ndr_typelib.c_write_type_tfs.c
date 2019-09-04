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
struct TYPE_8__ {int typekind; } ;
struct TYPE_7__ {int vt; int /*<<< orphan*/  hreftype; int /*<<< orphan*/  lpadesc; int /*<<< orphan*/  lptdesc; } ;
typedef  TYPE_1__ TYPEDESC ;
typedef  TYPE_2__ TYPEATTR ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_2__*) ; 
#define  TKIND_RECORD 131 
 int /*<<< orphan*/  TRACE (char*,int,char*) ; 
#define  VT_CARRAY 130 
#define  VT_PTR 129 
#define  VT_USERDEFINED 128 
 int /*<<< orphan*/  WRITE_SHORT (unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_base_type (int) ; 
 size_t write_array_tfs (int /*<<< orphan*/ *,unsigned char*,size_t*,int /*<<< orphan*/ ) ; 
 size_t write_oleaut_tfs (int) ; 
 size_t write_pointer_tfs (int /*<<< orphan*/ *,unsigned char*,size_t*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 size_t write_struct_tfs (int /*<<< orphan*/ *,unsigned char*,size_t*,TYPE_2__*) ; 

__attribute__((used)) static size_t write_type_tfs(ITypeInfo *typeinfo, unsigned char *str,
        size_t *len, TYPEDESC *desc, BOOL toplevel, BOOL onstack)
{
    ITypeInfo *refinfo;
    TYPEATTR *attr;
    size_t off;

    TRACE("vt %d%s\n", desc->vt, toplevel ? " (toplevel)" : "");

    if ((off = write_oleaut_tfs(desc->vt)))
        return off;

    switch (desc->vt)
    {
    case VT_PTR:
        return write_pointer_tfs(typeinfo, str, len, desc->lptdesc, toplevel, onstack);
    case VT_CARRAY:
        return write_array_tfs(typeinfo, str, len, desc->lpadesc);
    case VT_USERDEFINED:
        ITypeInfo_GetRefTypeInfo(typeinfo, desc->hreftype, &refinfo);
        ITypeInfo_GetTypeAttr(refinfo, &attr);

        switch (attr->typekind)
        {
        case TKIND_RECORD:
            off = write_struct_tfs(refinfo, str, len, attr);
            break;
        default:
            FIXME("unhandled kind %u\n", attr->typekind);
            off = *len;
            WRITE_SHORT(str, *len, 0);
            break;
        }

        ITypeInfo_ReleaseTypeAttr(refinfo, attr);
        ITypeInfo_Release(refinfo);
        break;
    default:
        /* base types are always embedded directly */
        assert(!get_base_type(desc->vt));
        FIXME("unhandled type %u\n", desc->vt);
        off = *len;
        WRITE_SHORT(str, *len, 0);
        break;
    }

    return off;
}