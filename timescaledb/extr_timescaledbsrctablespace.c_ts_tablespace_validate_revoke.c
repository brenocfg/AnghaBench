#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  objects; } ;
typedef  TYPE_1__ GrantStmt ;

/* Variables and functions */
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revoke_tuple_found ; 
 int /*<<< orphan*/  strVal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tablespace_validate_revoke_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
ts_tablespace_validate_revoke(GrantStmt *stmt)
{
	tablespace_validate_revoke_internal(strVal(linitial(stmt->objects)), revoke_tuple_found, stmt);
}