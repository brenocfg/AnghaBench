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
 scalar_t__ do_everything ; 
 int /*<<< orphan*/  do_server ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_server () ; 
 int /*<<< orphan*/  need_stub_files (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  write_server_routines (int /*<<< orphan*/  const*) ; 

void write_server(const statement_list_t *stmts)
{
    if (!do_server)
        return;
    if (do_everything && !need_stub_files(stmts))
        return;

    init_server();
    if (!server)
        return;

    write_server_routines( stmts );
    fclose(server);
}