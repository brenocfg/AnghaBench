#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  statement_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  indent ; 
 scalar_t__ need_inline_stubs_file (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  need_stub ; 
 int /*<<< orphan*/  print_server (char*) ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  server_token ; 
 int /*<<< orphan*/  write_exceptions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_expr_eval_routine_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_expr_eval_routines (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_formatstringsdecl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_procformatstring (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_rundown_routines () ; 
 int /*<<< orphan*/  write_server_stmts (int /*<<< orphan*/  const*,int,unsigned int*) ; 
 int /*<<< orphan*/  write_typeformatstring (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_user_quad_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_server_routines(const statement_list_t *stmts)
{
    unsigned int proc_offset = 0;
    int expr_eval_routines;

    if (need_inline_stubs_file( stmts ))
    {
        write_exceptions( server );
        print_server("\n");
        print_server("struct __server_frame\n");
        print_server("{\n");
        print_server("    __DECL_EXCEPTION_FRAME\n");
        print_server("    MIDL_STUB_MESSAGE _StubMsg;\n");
        print_server("};\n");
        print_server("\n");
        print_server("static int __server_filter( struct __server_frame *__frame )\n");
        print_server( "{\n");
        print_server( "    return (__frame->code == STATUS_ACCESS_VIOLATION) ||\n");
        print_server( "           (__frame->code == STATUS_DATATYPE_MISALIGNMENT) ||\n");
        print_server( "           (__frame->code == RPC_X_BAD_STUB_DATA) ||\n");
        print_server( "           (__frame->code == RPC_S_INVALID_BOUND);\n");
        print_server( "}\n");
        print_server( "\n");
    }

    write_formatstringsdecl(server, indent, stmts, need_stub);
    expr_eval_routines = write_expr_eval_routines(server, server_token);
    if (expr_eval_routines)
        write_expr_eval_routine_list(server, server_token);
    write_user_quad_list(server);
    write_rundown_routines();

    write_server_stmts(stmts, expr_eval_routines, &proc_offset);

    write_procformatstring(server, stmts, need_stub);
    write_typeformatstring(server, stmts, need_stub);
}