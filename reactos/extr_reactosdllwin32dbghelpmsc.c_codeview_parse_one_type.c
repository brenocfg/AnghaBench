#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_22__ ;
typedef  struct TYPE_35__   TYPE_21__ ;
typedef  struct TYPE_34__   TYPE_20__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_19__ ;
typedef  struct TYPE_31__   TYPE_18__ ;
typedef  struct TYPE_30__   TYPE_17__ ;
typedef  struct TYPE_29__   TYPE_16__ ;
typedef  struct TYPE_28__   TYPE_15__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct TYPE_34__ {int id; int /*<<< orphan*/  len; } ;
struct TYPE_32__ {int /*<<< orphan*/  arglist; int /*<<< orphan*/  rvtype; int /*<<< orphan*/  call; } ;
struct TYPE_31__ {int /*<<< orphan*/  arglist; int /*<<< orphan*/  rvtype; int /*<<< orphan*/  call; } ;
struct TYPE_30__ {int /*<<< orphan*/  arglist; int /*<<< orphan*/  rvtype; int /*<<< orphan*/  call; } ;
struct TYPE_29__ {int /*<<< orphan*/  arglist; int /*<<< orphan*/  rvtype; int /*<<< orphan*/  call; } ;
struct TYPE_28__ {char const* name; int /*<<< orphan*/  type; int /*<<< orphan*/  fieldlist; } ;
struct p_string {int dummy; } ;
struct TYPE_27__ {int /*<<< orphan*/  type; int /*<<< orphan*/  fieldlist; struct p_string const p_name; } ;
struct TYPE_26__ {int /*<<< orphan*/  type; int /*<<< orphan*/  fieldlist; struct p_string const p_name; } ;
struct TYPE_25__ {int property; int /*<<< orphan*/  fieldlist; int /*<<< orphan*/  un_len; } ;
struct TYPE_24__ {int property; int /*<<< orphan*/  fieldlist; int /*<<< orphan*/  un_len; } ;
struct TYPE_23__ {int property; int /*<<< orphan*/  fieldlist; int /*<<< orphan*/  un_len; } ;
struct TYPE_44__ {int property; int /*<<< orphan*/  fieldlist; int /*<<< orphan*/  structlen; } ;
struct TYPE_43__ {int property; int /*<<< orphan*/  fieldlist; int /*<<< orphan*/  structlen; } ;
struct TYPE_42__ {int property; int /*<<< orphan*/  fieldlist; int /*<<< orphan*/  structlen; } ;
struct TYPE_41__ {int /*<<< orphan*/  idxtype; int /*<<< orphan*/  elemtype; int /*<<< orphan*/  arrlen; } ;
struct TYPE_40__ {int /*<<< orphan*/  idxtype; int /*<<< orphan*/  elemtype; int /*<<< orphan*/  arrlen; } ;
struct TYPE_39__ {int /*<<< orphan*/  idxtype; int /*<<< orphan*/  elemtype; int /*<<< orphan*/  arrlen; } ;
struct TYPE_38__ {int /*<<< orphan*/  datatype; } ;
struct TYPE_37__ {int /*<<< orphan*/  datatype; } ;
struct TYPE_33__ {int attribute; int /*<<< orphan*/  type; } ;
struct TYPE_35__ {int attribute; int /*<<< orphan*/  type; } ;
union codeview_type {TYPE_20__ generic; TYPE_19__ mfunction_v2; TYPE_18__ mfunction_v1; TYPE_17__ procedure_v2; TYPE_16__ procedure_v1; TYPE_15__ enumeration_v3; TYPE_14__ enumeration_v2; TYPE_13__ enumeration_v1; TYPE_12__ union_v3; TYPE_11__ union_v2; TYPE_10__ union_v1; TYPE_9__ struct_v3; TYPE_8__ struct_v2; TYPE_7__ struct_v1; TYPE_6__ array_v3; TYPE_5__ array_v2; TYPE_4__ array_v1; TYPE_3__ pointer_v2; TYPE_2__ pointer_v1; TYPE_1__ modifier_v2; TYPE_21__ modifier_v1; } ;
struct symt_udt {int dummy; } ;
struct symt_function_signature {int dummy; } ;
struct symt {int dummy; } ;
struct codeview_type_parse {int /*<<< orphan*/  module; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_36__ {struct symt symt; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int const) ; 
#define  LF_ARRAY_V1 151 
#define  LF_ARRAY_V2 150 
#define  LF_ARRAY_V3 149 
#define  LF_CLASS_V1 148 
#define  LF_CLASS_V2 147 
#define  LF_CLASS_V3 146 
#define  LF_ENUM_V1 145 
#define  LF_ENUM_V2 144 
#define  LF_ENUM_V3 143 
#define  LF_MFUNCTION_V1 142 
#define  LF_MFUNCTION_V2 141 
#define  LF_MODIFIER_V1 140 
#define  LF_MODIFIER_V2 139 
#define  LF_POINTER_V1 138 
#define  LF_POINTER_V2 137 
#define  LF_PROCEDURE_V1 136 
#define  LF_PROCEDURE_V2 135 
#define  LF_STRUCTURE_V1 134 
#define  LF_STRUCTURE_V2 133 
#define  LF_STRUCTURE_V3 132 
#define  LF_UNION_V1 131 
#define  LF_UNION_V2 130 
#define  LF_UNION_V3 129 
#define  LF_VTSHAPE_V1 128 
 int /*<<< orphan*/  SymTagArrayType ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UdtClass ; 
 int /*<<< orphan*/  UdtStruct ; 
 int /*<<< orphan*/  UdtUnion ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  codeview_add_func_signature_args (struct codeview_type_parse*,struct symt_function_signature*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ codeview_add_type (unsigned int,struct symt*) ; 
 struct symt* codeview_add_type_array (struct codeview_type_parse*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct symt* codeview_add_type_enum (struct codeview_type_parse*,struct symt*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct symt* codeview_add_type_pointer (struct codeview_type_parse*,struct symt*,int /*<<< orphan*/ ) ; 
 struct symt* codeview_add_type_struct (struct codeview_type_parse*,struct symt*,char const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  codeview_add_type_struct_field_list (struct codeview_type_parse*,struct symt_udt*,int /*<<< orphan*/ ) ; 
 struct symt* codeview_cast_symt (struct symt*,int /*<<< orphan*/ ) ; 
 struct symt* codeview_fetch_type (struct codeview_type_parse*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct symt* codeview_get_type (unsigned int,int /*<<< orphan*/ ) ; 
 struct symt* codeview_new_func_signature (struct codeview_type_parse*,struct symt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump (union codeview_type const*,int /*<<< orphan*/ ) ; 
 int numeric_leaf (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 TYPE_22__* symt_new_udt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* terminate_string (struct p_string const*) ; 

__attribute__((used)) static struct symt* codeview_parse_one_type(struct codeview_type_parse* ctp,
                                            unsigned curr_type,
                                            const union codeview_type* type, BOOL details)
{
    struct symt*                symt;
    int                         value, leaf_len;
    const struct p_string*      p_name;
    const char*                 c_name;
    struct symt*                existing;

    existing = codeview_get_type(curr_type, TRUE);

    switch (type->generic.id)
    {
    case LF_MODIFIER_V1:
        /* FIXME: we don't handle modifiers,
         * but read previous type on the curr_type
         */
        WARN("Modifier on %x: %s%s%s%s\n",
             type->modifier_v1.type,
             type->modifier_v1.attribute & 0x01 ? "const " : "",
             type->modifier_v1.attribute & 0x02 ? "volatile " : "",
             type->modifier_v1.attribute & 0x04 ? "unaligned " : "",
             type->modifier_v1.attribute & ~0x07 ? "unknown " : "");
        symt = codeview_fetch_type(ctp, type->modifier_v1.type, details);
        break;
    case LF_MODIFIER_V2:
        /* FIXME: we don't handle modifiers, but readd previous type on the curr_type */
        WARN("Modifier on %x: %s%s%s%s\n",
             type->modifier_v2.type,
             type->modifier_v2.attribute & 0x01 ? "const " : "",
             type->modifier_v2.attribute & 0x02 ? "volatile " : "",
             type->modifier_v2.attribute & 0x04 ? "unaligned " : "",
             type->modifier_v2.attribute & ~0x07 ? "unknown " : "");
        symt = codeview_fetch_type(ctp, type->modifier_v2.type, details);
        break;

    case LF_POINTER_V1:
        symt = codeview_add_type_pointer(ctp, existing, type->pointer_v1.datatype);
        break;
    case LF_POINTER_V2:
        symt = codeview_add_type_pointer(ctp, existing, type->pointer_v2.datatype);
        break;

    case LF_ARRAY_V1:
        if (existing) symt = codeview_cast_symt(existing, SymTagArrayType);
        else
        {
            leaf_len = numeric_leaf(&value, &type->array_v1.arrlen);
            p_name = (const struct p_string*)((const unsigned char*)&type->array_v1.arrlen + leaf_len);
            symt = codeview_add_type_array(ctp, terminate_string(p_name),
                                           type->array_v1.elemtype,
                                           type->array_v1.idxtype, value);
        }
        break;
    case LF_ARRAY_V2:
        if (existing) symt = codeview_cast_symt(existing, SymTagArrayType);
        else
        {
            leaf_len = numeric_leaf(&value, &type->array_v2.arrlen);
            p_name = (const struct p_string*)((const unsigned char*)&type->array_v2.arrlen + leaf_len);

            symt = codeview_add_type_array(ctp, terminate_string(p_name),
                                           type->array_v2.elemtype,
                                           type->array_v2.idxtype, value);
        }
        break;
    case LF_ARRAY_V3:
        if (existing) symt = codeview_cast_symt(existing, SymTagArrayType);
        else
        {
            leaf_len = numeric_leaf(&value, &type->array_v3.arrlen);
            c_name = (const char*)&type->array_v3.arrlen + leaf_len;

            symt = codeview_add_type_array(ctp, c_name,
                                           type->array_v3.elemtype,
                                           type->array_v3.idxtype, value);
        }
        break;

    case LF_STRUCTURE_V1:
    case LF_CLASS_V1:
        leaf_len = numeric_leaf(&value, &type->struct_v1.structlen);
        p_name = (const struct p_string*)((const unsigned char*)&type->struct_v1.structlen + leaf_len);
        symt = codeview_add_type_struct(ctp, existing, terminate_string(p_name), value,
                                        type->generic.id == LF_CLASS_V1 ? UdtClass : UdtStruct,
                                        type->struct_v1.property);
        if (details)
        {
            codeview_add_type(curr_type, symt);
            if (!(type->struct_v1.property & 0x80)) /* 0x80 = forward declaration */
                codeview_add_type_struct_field_list(ctp, (struct symt_udt*)symt,
                                                    type->struct_v1.fieldlist);
        }
        break;

    case LF_STRUCTURE_V2:
    case LF_CLASS_V2:
        leaf_len = numeric_leaf(&value, &type->struct_v2.structlen);
        p_name = (const struct p_string*)((const unsigned char*)&type->struct_v2.structlen + leaf_len);
        symt = codeview_add_type_struct(ctp, existing, terminate_string(p_name), value,
                                        type->generic.id == LF_CLASS_V2 ? UdtClass : UdtStruct,
                                        type->struct_v2.property);
        if (details)
        {
            codeview_add_type(curr_type, symt);
            if (!(type->struct_v2.property & 0x80)) /* 0x80 = forward declaration */
                codeview_add_type_struct_field_list(ctp, (struct symt_udt*)symt,
                                                    type->struct_v2.fieldlist);
        }
        break;

    case LF_STRUCTURE_V3:
    case LF_CLASS_V3:
        leaf_len = numeric_leaf(&value, &type->struct_v3.structlen);
        c_name = (const char*)&type->struct_v3.structlen + leaf_len;
        symt = codeview_add_type_struct(ctp, existing, c_name, value,
                                        type->generic.id == LF_CLASS_V3 ? UdtClass : UdtStruct,
                                        type->struct_v3.property);
        if (details)
        {
            codeview_add_type(curr_type, symt);
            if (!(type->struct_v3.property & 0x80)) /* 0x80 = forward declaration */
                codeview_add_type_struct_field_list(ctp, (struct symt_udt*)symt,
                                                    type->struct_v3.fieldlist);
        }
        break;

    case LF_UNION_V1:
        leaf_len = numeric_leaf(&value, &type->union_v1.un_len);
        p_name = (const struct p_string*)((const unsigned char*)&type->union_v1.un_len + leaf_len);
        symt = codeview_add_type_struct(ctp, existing, terminate_string(p_name),
                                        value, UdtUnion, type->union_v1.property);
        if (details)
        {
            codeview_add_type(curr_type, symt);
            codeview_add_type_struct_field_list(ctp, (struct symt_udt*)symt,
                                                type->union_v1.fieldlist);
        }
        break;

    case LF_UNION_V2:
        leaf_len = numeric_leaf(&value, &type->union_v2.un_len);
        p_name = (const struct p_string*)((const unsigned char*)&type->union_v2.un_len + leaf_len);
        symt = codeview_add_type_struct(ctp, existing, terminate_string(p_name),
                                        value, UdtUnion, type->union_v2.property);
        if (details)
        {
            codeview_add_type(curr_type, symt);
            codeview_add_type_struct_field_list(ctp, (struct symt_udt*)symt,
                                                type->union_v2.fieldlist);
        }
        break;

    case LF_UNION_V3:
        leaf_len = numeric_leaf(&value, &type->union_v3.un_len);
        c_name = (const char*)&type->union_v3.un_len + leaf_len;
        symt = codeview_add_type_struct(ctp, existing, c_name,
                                        value, UdtUnion, type->union_v3.property);
        if (details)
        {
            codeview_add_type(curr_type, symt);
            codeview_add_type_struct_field_list(ctp, (struct symt_udt*)symt,
                                                type->union_v3.fieldlist);
        }
        break;

    case LF_ENUM_V1:
        symt = codeview_add_type_enum(ctp, existing,
                                      terminate_string(&type->enumeration_v1.p_name),
                                      type->enumeration_v1.fieldlist,
                                      type->enumeration_v1.type);
        break;

    case LF_ENUM_V2:
        symt = codeview_add_type_enum(ctp, existing,
                                      terminate_string(&type->enumeration_v2.p_name),
                                      type->enumeration_v2.fieldlist,
                                      type->enumeration_v2.type);
        break;

    case LF_ENUM_V3:
        symt = codeview_add_type_enum(ctp, existing, type->enumeration_v3.name,
                                      type->enumeration_v3.fieldlist,
                                      type->enumeration_v3.type);
        break;

    case LF_PROCEDURE_V1:
        symt = codeview_new_func_signature(ctp, existing, type->procedure_v1.call);
        if (details)
        {
            codeview_add_type(curr_type, symt);
            codeview_add_func_signature_args(ctp,
                                             (struct symt_function_signature*)symt,
                                             type->procedure_v1.rvtype,
                                             type->procedure_v1.arglist);
        }
        break;
    case LF_PROCEDURE_V2:
        symt = codeview_new_func_signature(ctp, existing,type->procedure_v2.call);
        if (details)
        {
            codeview_add_type(curr_type, symt);
            codeview_add_func_signature_args(ctp,
                                             (struct symt_function_signature*)symt,
                                             type->procedure_v2.rvtype,
                                             type->procedure_v2.arglist);
        }
        break;

    case LF_MFUNCTION_V1:
        /* FIXME: for C++, this is plain wrong, but as we don't use arg types
         * nor class information, this would just do for now
         */
        symt = codeview_new_func_signature(ctp, existing, type->mfunction_v1.call);
        if (details)
        {
            codeview_add_type(curr_type, symt);
            codeview_add_func_signature_args(ctp,
                                             (struct symt_function_signature*)symt,
                                             type->mfunction_v1.rvtype,
                                             type->mfunction_v1.arglist);
        }
        break;
    case LF_MFUNCTION_V2:
        /* FIXME: for C++, this is plain wrong, but as we don't use arg types
         * nor class information, this would just do for now
         */
        symt = codeview_new_func_signature(ctp, existing, type->mfunction_v2.call);
        if (details)
        {
            codeview_add_type(curr_type, symt);
            codeview_add_func_signature_args(ctp,
                                             (struct symt_function_signature*)symt,
                                             type->mfunction_v2.rvtype,
                                             type->mfunction_v2.arglist);
        }
        break;

    case LF_VTSHAPE_V1:
        /* this is an ugly hack... FIXME when we have C++ support */
        if (!(symt = existing))
        {
            char    buf[128];
            snprintf(buf, sizeof(buf), "__internal_vt_shape_%x\n", curr_type);
            symt = &symt_new_udt(ctp->module, buf, 0, UdtStruct)->symt;
        }
        break;
    default:
        FIXME("Unsupported type-id leaf %x\n", type->generic.id);
        dump(type, 2 + type->generic.len);
        return NULL;
    }
    return codeview_add_type(curr_type, symt) ? symt : NULL;
}