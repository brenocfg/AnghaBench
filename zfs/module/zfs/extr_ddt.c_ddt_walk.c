#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ ** spa_ddt; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  ddt_t ;
struct TYPE_9__ {scalar_t__ dde_type; scalar_t__ dde_class; } ;
typedef  TYPE_2__ ddt_entry_t ;
struct TYPE_10__ {scalar_t__ ddb_class; scalar_t__ ddb_type; scalar_t__ ddb_checksum; int /*<<< orphan*/  ddb_cursor; } ;
typedef  TYPE_3__ ddt_bookmark_t ;

/* Variables and functions */
 scalar_t__ DDT_CLASSES ; 
 scalar_t__ DDT_TYPES ; 
 int ENOENT ; 
 int SET_ERROR (int) ; 
 scalar_t__ ZIO_CHECKSUM_FUNCTIONS ; 
 scalar_t__ ddt_object_exists (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int ddt_object_walk (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *,TYPE_2__*) ; 

int
ddt_walk(spa_t *spa, ddt_bookmark_t *ddb, ddt_entry_t *dde)
{
	do {
		do {
			do {
				ddt_t *ddt = spa->spa_ddt[ddb->ddb_checksum];
				int error = ENOENT;
				if (ddt_object_exists(ddt, ddb->ddb_type,
				    ddb->ddb_class)) {
					error = ddt_object_walk(ddt,
					    ddb->ddb_type, ddb->ddb_class,
					    &ddb->ddb_cursor, dde);
				}
				dde->dde_type = ddb->ddb_type;
				dde->dde_class = ddb->ddb_class;
				if (error == 0)
					return (0);
				if (error != ENOENT)
					return (error);
				ddb->ddb_cursor = 0;
			} while (++ddb->ddb_checksum < ZIO_CHECKSUM_FUNCTIONS);
			ddb->ddb_checksum = 0;
		} while (++ddb->ddb_type < DDT_TYPES);
		ddb->ddb_type = 0;
	} while (++ddb->ddb_class < DDT_CLASSES);

	return (SET_ERROR(ENOENT));
}