#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_tablespaces; int capacity; TYPE_2__* tablespaces; } ;
typedef  TYPE_1__ Tablespaces ;
struct TYPE_8__ {int /*<<< orphan*/  tablespace_oid; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ Tablespace ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FormData_tablespace ;

/* Variables and functions */
 scalar_t__ TABLESPACE_DEFAULT_CAPACITY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* repalloc (TYPE_2__*,int) ; 

Tablespace *
ts_tablespaces_add(Tablespaces *tspcs, FormData_tablespace *form, Oid tspc_oid)
{
	Tablespace *tspc;

	if (tspcs->num_tablespaces >= tspcs->capacity)
	{
		tspcs->capacity += TABLESPACE_DEFAULT_CAPACITY;
		tspcs->tablespaces = repalloc(tspcs->tablespaces, sizeof(Tablespace) * tspcs->capacity);
	}

	tspc = &tspcs->tablespaces[tspcs->num_tablespaces++];
	memcpy(&tspc->fd, form, sizeof(FormData_tablespace));
	tspc->tablespace_oid = tspc_oid;

	return tspc;
}