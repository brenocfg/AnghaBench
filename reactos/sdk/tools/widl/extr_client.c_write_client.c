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
 int /*<<< orphan*/  do_client ; 
 scalar_t__ do_everything ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_client () ; 
 int /*<<< orphan*/  need_stub_files (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  write_client_routines (int /*<<< orphan*/  const*) ; 

void write_client(const statement_list_t *stmts)
{
    if (!do_client)
        return;
    if (do_everything && !need_stub_files(stmts))
        return;

    init_client();
    if (!client)
        return;

    write_client_routines( stmts );
    fclose(client);
}