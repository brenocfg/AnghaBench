#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  zprl_type; } ;
typedef  TYPE_1__ replication_level_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static boolean_t
is_raidz_mirror(replication_level_t *a, replication_level_t *b,
    replication_level_t **raidz, replication_level_t **mirror)
{
	if (strcmp(a->zprl_type, "raidz") == 0 &&
	    strcmp(b->zprl_type, "mirror") == 0) {
		*raidz = a;
		*mirror = b;
		return (B_TRUE);
	}
	return (B_FALSE);
}