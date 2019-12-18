#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int keysize; int entrysize; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ HASHCTL ;
typedef  int /*<<< orphan*/  DbHashEntry ;

/* Variables and functions */
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/ * hash_create (char*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ts_guc_max_background_workers ; 

__attribute__((used)) static HTAB *
init_database_htab(void)
{
	HASHCTL info = { .keysize = sizeof(Oid), .entrysize = sizeof(DbHashEntry) };

	return hash_create("launcher_db_htab",
					   ts_guc_max_background_workers,
					   &info,
					   HASH_BLOBS | HASH_ELEM);
}