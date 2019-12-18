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
struct TYPE_3__ {int /*<<< orphan*/  tree; } ;
typedef  TYPE_1__ zed_strings_t ;
typedef  int /*<<< orphan*/  zed_strings_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/ * _zed_strings_node_create (char const*,char const*) ; 
 int /*<<< orphan*/  _zed_strings_node_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avl_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 

int
zed_strings_add(zed_strings_t *zsp, const char *key, const char *s)
{
	zed_strings_node_t *newp, *oldp;

	if (!zsp || !s) {
		errno = EINVAL;
		return (-1);
	}
	if (key == s)
		key = NULL;

	newp = _zed_strings_node_create(key, s);
	if (!newp)
		return (-1);

	oldp = avl_find(&zsp->tree, newp, NULL);
	if (oldp) {
		avl_remove(&zsp->tree, oldp);
		_zed_strings_node_destroy(oldp);
	}
	avl_add(&zsp->tree, newp);
	return (0);
}