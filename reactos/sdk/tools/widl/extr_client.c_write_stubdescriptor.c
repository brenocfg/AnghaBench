#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ var_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_2__ type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_IMPLICIT_HANDLE ; 
 scalar_t__ MODE_Oif ; 
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  generic_handle_list ; 
 TYPE_1__* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_stub_mode () ; 
 int /*<<< orphan*/  indent ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_client (char*,...) ; 
 int /*<<< orphan*/  user_type_list ; 

__attribute__((used)) static void write_stubdescriptor(type_t *iface, int expr_eval_routines)
{
    const var_t *implicit_handle = get_attrp(iface->attrs, ATTR_IMPLICIT_HANDLE);

    print_client("static const MIDL_STUB_DESC %s_StubDesc =\n", iface->name);
    print_client("{\n");
    indent++;
    print_client("(void *)& %s___RpcClientInterface,\n", iface->name);
    print_client("MIDL_user_allocate,\n");
    print_client("MIDL_user_free,\n");
    print_client("{\n");
    indent++;
    if (implicit_handle)
        print_client("&%s,\n", implicit_handle->name);
    else
        print_client("&%s__MIDL_AutoBindHandle,\n", iface->name);
    indent--;
    print_client("},\n");
    print_client("0,\n");
    if (!list_empty( &generic_handle_list ))
        print_client("BindingRoutines,\n");
    else
        print_client("0,\n");
    if (expr_eval_routines)
        print_client("ExprEvalRoutines,\n");
    else
        print_client("0,\n");
    print_client("0,\n");
    print_client("__MIDL_TypeFormatString.Format,\n");
    print_client("1, /* -error bounds_check flag */\n");
    print_client("0x%x, /* Ndr library version */\n", get_stub_mode() == MODE_Oif ? 0x50002 : 0x10001);
    print_client("0,\n");
    print_client("0x50100a4, /* MIDL Version 5.1.164 */\n");
    print_client("0,\n");
    print_client("%s,\n", list_empty(&user_type_list) ? "0" : "UserMarshalRoutines");
    print_client("0,  /* notify & notify_flag routine table */\n");
    print_client("1,  /* Flags */\n");
    print_client("0,  /* Reserved3 */\n");
    print_client("0,  /* Reserved4 */\n");
    print_client("0   /* Reserved5 */\n");
    indent--;
    print_client("};\n");
    fprintf(client, "\n");
}