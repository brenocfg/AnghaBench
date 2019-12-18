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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  DropStmt ;

/* Variables and functions */
 int /*<<< orphan*/  drop_statement_drops_extension (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
should_load_on_drop_extension(Node *utility_stmt)
{
	return !drop_statement_drops_extension((DropStmt *) utility_stmt);
}