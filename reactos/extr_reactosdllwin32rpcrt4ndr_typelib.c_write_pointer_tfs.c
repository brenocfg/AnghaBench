#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ vt; int /*<<< orphan*/  hreftype; } ;
struct TYPE_9__ {int typekind; TYPE_1__ tdescAlias; int /*<<< orphan*/  cImplTypes; int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ TYPEDESC ;
typedef  TYPE_2__ TYPEATTR ;
typedef  int /*<<< orphan*/  ITypeInfo ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 unsigned char FC_ALLOCED_ON_STACK ; 
 unsigned char FC_ENUM32 ; 
 unsigned char FC_PAD ; 
 unsigned char FC_POINTER_DEREF ; 
 unsigned char FC_RP ; 
 unsigned char FC_SIMPLE_POINTER ; 
 unsigned char FC_UP ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  ITypeInfo_GetRefTypeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ITypeInfo_GetTypeAttr (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  ITypeInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ITypeInfo_ReleaseTypeAttr (int /*<<< orphan*/ *,TYPE_2__*) ; 
#define  TKIND_ALIAS 133 
#define  TKIND_COCLASS 132 
#define  TKIND_DISPATCH 131 
#define  TKIND_ENUM 130 
#define  TKIND_INTERFACE 129 
#define  TKIND_RECORD 128 
 scalar_t__ VT_DISPATCH ; 
 scalar_t__ VT_PTR ; 
 scalar_t__ VT_UNKNOWN ; 
 scalar_t__ VT_USERDEFINED ; 
 int /*<<< orphan*/  WRITE_CHAR (unsigned char*,size_t,unsigned char) ; 
 int /*<<< orphan*/  WRITE_SHORT (unsigned char*,size_t,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned char get_base_type (scalar_t__) ; 
 int /*<<< orphan*/  get_default_iface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_ip_tfs (unsigned char*,size_t*,int /*<<< orphan*/ *) ; 
 size_t write_struct_tfs (int /*<<< orphan*/ *,unsigned char*,size_t*,TYPE_2__*) ; 
 size_t write_type_tfs (int /*<<< orphan*/ *,unsigned char*,size_t*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t write_pointer_tfs(ITypeInfo *typeinfo, unsigned char *str,
        size_t *len, TYPEDESC *desc, BOOL toplevel, BOOL onstack)
{
    unsigned char basetype, flags = 0;
    size_t ref, off = *len;
    ITypeInfo *refinfo;
    TYPEATTR *attr;
    GUID guid;

    if (desc->vt == VT_USERDEFINED)
    {
        ITypeInfo_GetRefTypeInfo(typeinfo, desc->hreftype, &refinfo);
        ITypeInfo_GetTypeAttr(refinfo, &attr);

        switch (attr->typekind)
        {
        case TKIND_ENUM:
            assert(!toplevel);  /* toplevel base-type pointers should use IsSimpleRef */
            WRITE_CHAR(str, *len, FC_UP);
            WRITE_CHAR(str, *len, FC_SIMPLE_POINTER);
            WRITE_CHAR(str, *len, FC_ENUM32);
            WRITE_CHAR(str, *len, FC_PAD);
            break;
        case TKIND_RECORD:
            assert(!toplevel);  /* toplevel struct pointers should use IsSimpleRef */
            ref = write_struct_tfs(refinfo, str, len, attr);
            off = *len;
            WRITE_CHAR (str, *len, FC_UP);
            WRITE_CHAR (str, *len, 0);
            WRITE_SHORT(str, *len, ref - *len);
            break;
        case TKIND_INTERFACE:
        case TKIND_DISPATCH:
            write_ip_tfs(str, len, &attr->guid);
            break;
        case TKIND_COCLASS:
            get_default_iface(refinfo, attr->cImplTypes, &guid);
            write_ip_tfs(str, len, &guid);
            break;
        case TKIND_ALIAS:
            off = write_pointer_tfs(refinfo, str, len, &attr->tdescAlias, toplevel, onstack);
            break;
        default:
            FIXME("unhandled kind %#x\n", attr->typekind);
            WRITE_SHORT(str, *len, 0);
            break;
        }

        ITypeInfo_ReleaseTypeAttr(refinfo, attr);
        ITypeInfo_Release(refinfo);
    }
    else if ((basetype = get_base_type(desc->vt)))
    {
        assert(!toplevel); /* toplevel base-type pointers should use IsSimpleRef */
        WRITE_CHAR(str, *len, FC_UP);
        WRITE_CHAR(str, *len, FC_SIMPLE_POINTER);
        WRITE_CHAR(str, *len, basetype);
        WRITE_CHAR(str, *len, FC_PAD);
    }
    else
    {
        ref = write_type_tfs(typeinfo, str, len, desc, FALSE, FALSE);

        if (onstack) flags |= FC_ALLOCED_ON_STACK;
        if (desc->vt == VT_PTR || desc->vt == VT_UNKNOWN || desc->vt == VT_DISPATCH)
            flags |= FC_POINTER_DEREF;

        off = *len;

        WRITE_CHAR (str, *len, toplevel ? FC_RP : FC_UP);
        WRITE_CHAR (str, *len, flags);
        WRITE_SHORT(str, *len, ref - *len);
    }

    return off;
}