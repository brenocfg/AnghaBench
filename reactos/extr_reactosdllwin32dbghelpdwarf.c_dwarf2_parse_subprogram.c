#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_9__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_39__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;

/* Type definitions */
struct vector {int dummy; } ;
struct symt_function_signature {int /*<<< orphan*/  symt; } ;
struct symt {int dummy; } ;
struct TYPE_40__ {scalar_t__ uvalue; int /*<<< orphan*/  string; } ;
struct attribute {scalar_t__ gotten_from; TYPE_1__ u; } ;
struct TYPE_47__ {scalar_t__ kind; scalar_t__ offset; int /*<<< orphan*/  reg; } ;
struct TYPE_43__ {TYPE_6__* func; TYPE_4__* ctx; TYPE_9__ frame; scalar_t__ non_computed_variable; } ;
typedef  TYPE_3__ dwarf2_subprogram_t ;
struct TYPE_44__ {int /*<<< orphan*/  module; scalar_t__ load_offset; int /*<<< orphan*/  compiland; struct symt** symt_cache; int /*<<< orphan*/  thunks; } ;
typedef  TYPE_4__ dwarf2_parse_context_t ;
struct TYPE_45__ {struct symt* symt; TYPE_2__* abbrev; } ;
typedef  TYPE_5__ dwarf2_debug_info_t ;
struct TYPE_46__ {struct symt symt; } ;
struct TYPE_42__ {int /*<<< orphan*/  frame_regno; } ;
struct TYPE_41__ {int tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CV_CALL_FAR_C ; 
 int /*<<< orphan*/  DW_AT_declaration ; 
 int /*<<< orphan*/  DW_AT_frame_base ; 
 int /*<<< orphan*/  DW_AT_inline ; 
 int /*<<< orphan*/  DW_AT_name ; 
 scalar_t__ DW_INL_not_inlined ; 
#define  DW_TAG_GNU_call_site 146 
#define  DW_TAG_GNU_formal_parameter_pack 145 
#define  DW_TAG_GNU_template_parameter_pack 144 
#define  DW_TAG_class_type 143 
#define  DW_TAG_const_type 142 
#define  DW_TAG_enumeration_type 141 
#define  DW_TAG_formal_parameter 140 
#define  DW_TAG_inlined_subroutine 139 
#define  DW_TAG_label 138 
#define  DW_TAG_lexical_block 137 
#define  DW_TAG_pointer_type 136 
#define  DW_TAG_structure_type 135 
#define  DW_TAG_subprogram 134 
#define  DW_TAG_template_type_param 133 
#define  DW_TAG_template_value_param 132 
#define  DW_TAG_typedef 131 
#define  DW_TAG_union_type 130 
#define  DW_TAG_unspecified_parameters 129 
#define  DW_TAG_variable 128 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SymTagCustom ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  assert (struct symt*) ; 
 scalar_t__ attr_direct ; 
 TYPE_39__* dbghelp_current_cpu ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2_compute_location_attr (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf2_debug_ctx (TYPE_4__*) ; 
 scalar_t__ dwarf2_debug_di (TYPE_5__*) ; 
 scalar_t__ dwarf2_find_attribute (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,struct attribute*) ; 
 int /*<<< orphan*/  dwarf2_get_cpp_name (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 struct vector* dwarf2_get_di_children (TYPE_4__*,TYPE_5__*) ; 
 struct symt* dwarf2_lookup_type (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dwarf2_parse_const_type (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dwarf2_parse_inlined_subroutine (TYPE_3__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  dwarf2_parse_pointer_type (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dwarf2_parse_subprogram_block (TYPE_3__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  dwarf2_parse_subprogram_label (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  dwarf2_parse_variable (TYPE_3__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  dwarf2_read_range (TYPE_4__*,TYPE_5__*,unsigned long*,unsigned long*) ; 
 scalar_t__ elf_is_in_thunk_area (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ loc_regrel ; 
 scalar_t__ loc_user ; 
 size_t sc_void ; 
 int /*<<< orphan*/  symt_add_function_point (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* symt_new_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned long,int /*<<< orphan*/ *) ; 
 struct symt_function_signature* symt_new_function_signature (int /*<<< orphan*/ ,struct symt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symt_normalize_function (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ vector_at (struct vector*,unsigned int) ; 
 unsigned int vector_length (struct vector*) ; 

__attribute__((used)) static struct symt* dwarf2_parse_subprogram(dwarf2_parse_context_t* ctx,
                                            dwarf2_debug_info_t* di)
{
    struct attribute name;
    unsigned long low_pc, high_pc;
    struct attribute is_decl;
    struct attribute inline_flags;
    struct symt* ret_type;
    struct symt_function_signature* sig_type;
    dwarf2_subprogram_t subpgm;
    struct vector* children;
    dwarf2_debug_info_t* child;
    unsigned int i;

    if (di->symt) return di->symt;

    TRACE("%s, for %s\n", dwarf2_debug_ctx(ctx), dwarf2_debug_di(di));

    if (!dwarf2_find_attribute(ctx, di, DW_AT_name, &name))
    {
        WARN("No name for function... dropping function\n");
        return NULL;
    }
    /* if it's an abstract representation of an inline function, there should be
     * a concrete object that we'll handle
     */
    if (dwarf2_find_attribute(ctx, di, DW_AT_inline, &inline_flags) &&
        inline_flags.u.uvalue != DW_INL_not_inlined)
    {
        TRACE("Function %s declared as inlined (%ld)... skipping\n",
              debugstr_a(name.u.string), inline_flags.u.uvalue);
        return NULL;
    }

    if (dwarf2_find_attribute(ctx, di, DW_AT_declaration, &is_decl) &&
        is_decl.u.uvalue && is_decl.gotten_from == attr_direct)
    {
        /* it's a real declaration, skip it */
        return NULL;
    }
    if (!dwarf2_read_range(ctx, di, &low_pc, &high_pc))
    {
        WARN("cannot get range for %s\n", name.u.string);
        return NULL;
    }
    /* As functions (defined as inline assembly) get debug info with dwarf
     * (not the case for stabs), we just drop Wine's thunks here...
     * Actual thunks will be created in elf_module from the symbol table
     */
#ifndef DBGHELP_STATIC_LIB
    if (elf_is_in_thunk_area(ctx->load_offset + low_pc, ctx->thunks) >= 0)
        return NULL;
#endif
    if (!(ret_type = dwarf2_lookup_type(ctx, di)))
    {
        ret_type = ctx->symt_cache[sc_void];
        assert(ret_type);
    }
    /* FIXME: assuming C source code */
    sig_type = symt_new_function_signature(ctx->module, ret_type, CV_CALL_FAR_C);
    subpgm.func = symt_new_function(ctx->module, ctx->compiland,
                                    dwarf2_get_cpp_name(ctx, di, name.u.string),
                                    ctx->load_offset + low_pc, high_pc - low_pc,
                                    &sig_type->symt);
    di->symt = &subpgm.func->symt;
    subpgm.ctx = ctx;
    if (!dwarf2_compute_location_attr(ctx, di, DW_AT_frame_base,
                                      &subpgm.frame, NULL))
    {
        /* on stack !! */
        subpgm.frame.kind = loc_regrel;
        subpgm.frame.reg = dbghelp_current_cpu->frame_regno;
        subpgm.frame.offset = 0;
    }
    subpgm.non_computed_variable = FALSE;

    children = dwarf2_get_di_children(ctx, di);
    if (children) for (i = 0; i < vector_length(children); i++)
    {
        child = *(dwarf2_debug_info_t**)vector_at(children, i);

        switch (child->abbrev->tag)
        {
        case DW_TAG_variable:
        case DW_TAG_formal_parameter:
            dwarf2_parse_variable(&subpgm, NULL, child);
            break;
        case DW_TAG_lexical_block:
            dwarf2_parse_subprogram_block(&subpgm, NULL, child);
            break;
        case DW_TAG_inlined_subroutine:
            dwarf2_parse_inlined_subroutine(&subpgm, NULL, child);
            break;
        case DW_TAG_pointer_type:
            dwarf2_parse_pointer_type(subpgm.ctx, di);
            break;
        case DW_TAG_const_type:
            dwarf2_parse_const_type(subpgm.ctx, di);
            break;
        case DW_TAG_subprogram:
            /* FIXME: likely a declaration (to be checked)
             * skip it for now
             */
            break;
        case DW_TAG_label:
            dwarf2_parse_subprogram_label(&subpgm, child);
            break;
        case DW_TAG_class_type:
        case DW_TAG_structure_type:
        case DW_TAG_union_type:
        case DW_TAG_enumeration_type:
        case DW_TAG_typedef:
            /* the type referred to will be loaded when we need it, so skip it */
            break;
        case DW_TAG_unspecified_parameters:
        case DW_TAG_template_type_param:
        case DW_TAG_template_value_param:
        case DW_TAG_GNU_call_site:
        case DW_TAG_GNU_template_parameter_pack:
        case DW_TAG_GNU_formal_parameter_pack:
            /* FIXME: no support in dbghelp's internals so far */
            break;
        default:
            FIXME("Unhandled Tag type 0x%lx at %s, for %s\n",
                  child->abbrev->tag, dwarf2_debug_ctx(ctx), dwarf2_debug_di(di));
	}
    }

    if (subpgm.non_computed_variable || subpgm.frame.kind >= loc_user)
    {
        symt_add_function_point(ctx->module, subpgm.func, SymTagCustom,
                                &subpgm.frame, NULL);
    }
    if (subpgm.func) symt_normalize_function(subpgm.ctx->module, subpgm.func);

    return di->symt;
}