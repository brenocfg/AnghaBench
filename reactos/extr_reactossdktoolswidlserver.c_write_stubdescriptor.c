#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ type_t ;

/* Variables and functions */
 scalar_t__ MODE_Oif ; 
 int /*<<< orphan*/  context_handle_list ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_stub_mode () ; 
 int /*<<< orphan*/  indent ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_server (char*,...) ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  user_type_list ; 

__attribute__((used)) static void write_stubdescriptor(type_t *iface, int expr_eval_routines)
{
    print_server("static const MIDL_STUB_DESC %s_StubDesc =\n", iface->name);
    print_server("{\n");
    indent++;
    print_server("(void *)& %s___RpcServerInterface,\n", iface->name);
    print_server("MIDL_user_allocate,\n");
    print_server("MIDL_user_free,\n");
    print_server("{\n");
    indent++;
    print_server("0,\n");
    indent--;
    print_server("},\n");
    if (!list_empty( &context_handle_list ))
        print_server("RundownRoutines,\n");
    else
        print_server("0,\n");
    print_server("0,\n");
    if (expr_eval_routines)
        print_server("ExprEvalRoutines,\n");
    else
        print_server("0,\n");
    print_server("0,\n");
    print_server("__MIDL_TypeFormatString.Format,\n");
    print_server("1, /* -error bounds_check flag */\n");
    print_server("0x%x, /* Ndr library version */\n", get_stub_mode() == MODE_Oif ? 0x50002 : 0x10001);
    print_server("0,\n");
    print_server("0x50100a4, /* MIDL Version 5.1.164 */\n");
    print_server("0,\n");
    print_server("%s,\n", list_empty(&user_type_list) ? "0" : "UserMarshalRoutines");
    print_server("0,  /* notify & notify_flag routine table */\n");
    print_server("1,  /* Flags */\n");
    print_server("0,  /* Reserved3 */\n");
    print_server("0,  /* Reserved4 */\n");
    print_server("0   /* Reserved5 */\n");
    indent--;
    print_server("};\n");
    fprintf(server, "\n");
}