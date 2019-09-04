#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type_t ;
typedef  int /*<<< orphan*/  msft_typelib_t ;
struct TYPE_4__ {int /*<<< orphan*/  sval; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  cval; TYPE_1__ u; } ;
typedef  TYPE_2__ expr_t ;

/* Variables and functions */
 scalar_t__ EXPR_STRLIT ; 
 scalar_t__ EXPR_WSTRLIT ; 
 scalar_t__ TYPE_ENUM ; 
#define  VT_BOOL 138 
 int VT_BSTR ; 
#define  VT_HRESULT 137 
#define  VT_I1 136 
#define  VT_I2 135 
#define  VT_I4 134 
#define  VT_INT 133 
#define  VT_R4 132 
#define  VT_UI1 131 
#define  VT_UI2 130 
#define  VT_UI4 129 
#define  VT_UINT 128 
 int VT_USERDEFINED ; 
 int /*<<< orphan*/  chat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int get_type_vt (int /*<<< orphan*/ *) ; 
 scalar_t__ is_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ type_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * type_pointer_get_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (char*,...) ; 
 int /*<<< orphan*/  write_int_value (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_string_value (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_default_value(msft_typelib_t *typelib, type_t *type, expr_t *expr, int *out)
{
    int vt;

    if (expr->type == EXPR_STRLIT || expr->type == EXPR_WSTRLIT) {
        if (get_type_vt(type) != VT_BSTR)
            error("string default value applied to non-string type\n");
        chat("default value '%s'\n", expr->u.sval);
        write_string_value(typelib, out, expr->u.sval);
        return;
    }

    if (type_get_type(type) == TYPE_ENUM) {
        vt = VT_I4;
    } else if (is_ptr(type)) {
        vt = get_type_vt(type_pointer_get_ref(type));
        if (vt == VT_USERDEFINED)
            vt = VT_I4;
        if (expr->cval)
            warning("non-null pointer default value\n");
    } else {
        vt = get_type_vt(type);
        switch(vt) {
        case VT_I2:
        case VT_I4:
        case VT_R4:
        case VT_BOOL:
        case VT_I1:
        case VT_UI1:
        case VT_UI2:
        case VT_UI4:
        case VT_INT:
        case VT_UINT:
        case VT_HRESULT:
            break;
        default:
            warning("can't write value of type %d yet\n", vt);
            return;
        }
    }

    write_int_value(typelib, out, vt, expr->cval);
}