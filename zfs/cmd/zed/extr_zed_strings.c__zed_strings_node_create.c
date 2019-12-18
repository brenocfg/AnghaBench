#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* val; void* key; } ;
typedef  TYPE_1__ zed_strings_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zed_strings_node_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 void* strdup (char const*) ; 

zed_strings_node_t *
_zed_strings_node_create(const char *key, const char *val)
{
	zed_strings_node_t *np;

	assert(val != NULL);

	np = calloc(1, sizeof (*np));
	if (!np)
		return (NULL);

	np->val = strdup(val);
	if (!np->val)
		goto nomem;

	if (key) {
		np->key = strdup(key);
		if (!np->key)
			goto nomem;
	} else {
		np->key = np->val;
	}
	return (np);

nomem:
	_zed_strings_node_destroy(np);
	return (NULL);
}