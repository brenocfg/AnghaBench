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
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  client_token ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  indent ; 
 scalar_t__ need_inline_stubs_file (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  need_stub ; 
 int /*<<< orphan*/  print_client (char*) ; 
 int /*<<< orphan*/  write_client_ifaces (int /*<<< orphan*/  const*,int,unsigned int*) ; 
 int /*<<< orphan*/  write_exceptions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_expr_eval_routine_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_expr_eval_routines (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_formatstringsdecl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_generic_handle_routine_list () ; 
 int /*<<< orphan*/  write_procformatstring (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_typeformatstring (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_user_quad_list (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_client_routines(const statement_list_t *stmts)
{
    unsigned int proc_offset = 0;
    int expr_eval_routines;

    if (need_inline_stubs_file( stmts ))
    {
        write_exceptions( client );
        print_client( "\n");
    }

    write_formatstringsdecl(client, indent, stmts, need_stub);
    expr_eval_routines = write_expr_eval_routines(client, client_token);
    if (expr_eval_routines)
        write_expr_eval_routine_list(client, client_token);
    write_generic_handle_routine_list();
    write_user_quad_list(client);

    write_client_ifaces(stmts, expr_eval_routines, &proc_offset);

    fprintf(client, "\n");

    write_procformatstring(client, stmts, need_stub);
    write_typeformatstring(client, stmts, need_stub);
}