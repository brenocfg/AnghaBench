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
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 char* get_attname_compat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_attnum (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static AttrNumber
chunk_get_attno(Oid hypertable_relid, Oid chunk_relid, AttrNumber hypertable_attnum)
{
	const char *attname = get_attname_compat(hypertable_relid, hypertable_attnum, false);

	return get_attnum(chunk_relid, attname);
}