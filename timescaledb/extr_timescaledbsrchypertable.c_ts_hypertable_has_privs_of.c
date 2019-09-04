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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int has_privs_of_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_rel_get_owner (int /*<<< orphan*/ ) ; 

bool
ts_hypertable_has_privs_of(Oid hypertable_oid, Oid userid)
{
	return has_privs_of_role(userid, ts_rel_get_owner(hypertable_oid));
}