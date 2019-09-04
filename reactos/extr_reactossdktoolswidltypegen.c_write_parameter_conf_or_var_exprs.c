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
struct TYPE_8__ {int /*<<< orphan*/  attrs; int /*<<< orphan*/ * type; } ;
typedef  TYPE_1__ var_t ;
typedef  int /*<<< orphan*/  type_t ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ expr_t ;
typedef  enum remoting_phase { ____Placeholder_remoting_phase } remoting_phase ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_IIDIS ; 
 int /*<<< orphan*/  ATTR_SWITCHIS ; 
 int /*<<< orphan*/  EXPR_VOID ; 
 int TDT_IGNORE_RANGES ; 
 int TDT_IGNORE_STRINGS ; 
#define  TGT_ARRAY 140 
#define  TGT_BASIC 139 
#define  TGT_CTXT_HANDLE 138 
#define  TGT_CTXT_HANDLE_POINTER 137 
#define  TGT_ENUM 136 
#define  TGT_IFACE_POINTER 135 
#define  TGT_INVALID 134 
#define  TGT_POINTER 133 
#define  TGT_RANGE 132 
#define  TGT_STRING 131 
#define  TGT_STRUCT 130 
#define  TGT_UNION 129 
#define  TGT_USER_TYPE 128 
 int /*<<< orphan*/  TYPE_UNION ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_conformance_needed_for_phase (int) ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,int,char*) ; 
 TYPE_2__* type_array_get_conformance (int /*<<< orphan*/  const*) ; 
 TYPE_2__* type_array_get_variance (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  type_array_has_conformance (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  type_array_has_variance (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  type_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * type_pointer_get_ref (int /*<<< orphan*/  const*) ; 
 int typegen_detect_type (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_expr (int /*<<< orphan*/ *,TYPE_2__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

void write_parameter_conf_or_var_exprs(FILE *file, int indent, const char *local_var_prefix,
                                       enum remoting_phase phase, const var_t *var, int valid_variance)
{
    const type_t *type = var->type;
    /* get fundamental type for the argument */
    for (;;)
    {
        switch (typegen_detect_type(type, var->attrs, TDT_IGNORE_STRINGS|TDT_IGNORE_RANGES))
        {
        case TGT_ARRAY:
            if (is_conformance_needed_for_phase(phase))
            {
                if (type_array_has_conformance(type) &&
                    type_array_get_conformance(type)->type != EXPR_VOID)
                {
                    print_file(file, indent, "__frame->_StubMsg.MaxCount = (ULONG_PTR)");
                    write_expr(file, type_array_get_conformance(type), 1, 1, NULL, NULL, local_var_prefix);
                    fprintf(file, ";\n\n");
                }
                if (type_array_has_variance(type))
                {
                    print_file(file, indent, "__frame->_StubMsg.Offset = 0;\n"); /* FIXME */
                    if (valid_variance)
                    {
                        print_file(file, indent, "__frame->_StubMsg.ActualCount = (ULONG_PTR)");
                        write_expr(file, type_array_get_variance(type), 1, 1, NULL, NULL, local_var_prefix);
                        fprintf(file, ";\n\n");
                    }
                    else
                        print_file(file, indent, "__frame->_StubMsg.ActualCount = __frame->_StubMsg.MaxCount;\n\n");
                }
            }
            break;
        case TGT_UNION:
            if (type_get_type(type) == TYPE_UNION &&
                is_conformance_needed_for_phase(phase))
            {
                print_file(file, indent, "__frame->_StubMsg.MaxCount = (ULONG_PTR)");
                write_expr(file, get_attrp(var->attrs, ATTR_SWITCHIS), 1, 1, NULL, NULL, local_var_prefix);
                fprintf(file, ";\n\n");
            }
            break;
        case TGT_IFACE_POINTER:
        {
            expr_t *iid;

            if (is_conformance_needed_for_phase(phase) && (iid = get_attrp( var->attrs, ATTR_IIDIS )))
            {
                print_file( file, indent, "__frame->_StubMsg.MaxCount = (ULONG_PTR) " );
                write_expr( file, iid, 1, 1, NULL, NULL, local_var_prefix );
                fprintf( file, ";\n\n" );
            }
            break;
        }
        case TGT_POINTER:
            type = type_pointer_get_ref(type);
            continue;
        case TGT_INVALID:
        case TGT_USER_TYPE:
        case TGT_CTXT_HANDLE:
        case TGT_CTXT_HANDLE_POINTER:
        case TGT_STRING:
        case TGT_BASIC:
        case TGT_ENUM:
        case TGT_STRUCT:
        case TGT_RANGE:
            break;
        }
        break;
    }
}