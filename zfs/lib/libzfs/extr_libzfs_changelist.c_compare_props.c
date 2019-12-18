#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_prop_t ;
typedef  int /*<<< orphan*/  propb ;
typedef  int /*<<< orphan*/  propa ;
struct TYPE_2__ {int /*<<< orphan*/  cn_handle; } ;
typedef  TYPE_1__ prop_changenode_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int MAXPATHLEN ; 
 int strcmp (char*,char*) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_props(const void *a, const void *b, zfs_prop_t prop)
{
	const prop_changenode_t *ca = a;
	const prop_changenode_t *cb = b;

	char propa[MAXPATHLEN];
	char propb[MAXPATHLEN];

	boolean_t haspropa, haspropb;

	haspropa = (zfs_prop_get(ca->cn_handle, prop, propa, sizeof (propa),
	    NULL, NULL, 0, B_FALSE) == 0);
	haspropb = (zfs_prop_get(cb->cn_handle, prop, propb, sizeof (propb),
	    NULL, NULL, 0, B_FALSE) == 0);

	if (!haspropa && haspropb)
		return (-1);
	else if (haspropa && !haspropb)
		return (1);
	else if (!haspropa && !haspropb)
		return (0);
	else
		return (strcmp(propb, propa));
}