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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_relname_relid (char*,int /*<<< orphan*/ ) ; 
 char* makeObjectName (char const*,char const*,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char *
chunk_index_choose_name(const char *tabname, const char *main_index_name, Oid namespaceid)
{
	char buf[10];
	char *label = NULL;
	char *idxname;
	int n = 0;

	for (;;)
	{
		/* makeObjectName will ensure the index name fits within a NAME type */
		idxname = makeObjectName(tabname, main_index_name, label);

		if (!OidIsValid(get_relname_relid(idxname, namespaceid)))
			break;

		/* found a conflict, so try a new name component */
		pfree(idxname);
		snprintf(buf, sizeof(buf), "%d", ++n);
		label = buf;
	}

	return idxname;
}