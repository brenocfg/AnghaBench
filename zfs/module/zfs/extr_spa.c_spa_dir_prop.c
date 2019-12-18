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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  spa_meta_objset; } ;
typedef  TYPE_1__ spa_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int ENOENT ; 
 int /*<<< orphan*/  spa_load_failed (TYPE_1__*,char*,char const*,int) ; 
 int zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
spa_dir_prop(spa_t *spa, const char *name, uint64_t *val, boolean_t log_enoent)
{
	int error = zap_lookup(spa->spa_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
	    name, sizeof (uint64_t), 1, val);

	if (error != 0 && (error != ENOENT || log_enoent)) {
		spa_load_failed(spa, "couldn't get '%s' value in MOS directory "
		    "[error=%d]", name, error);
	}

	return (error);
}