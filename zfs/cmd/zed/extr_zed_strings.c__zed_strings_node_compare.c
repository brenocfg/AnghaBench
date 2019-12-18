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
struct TYPE_2__ {char* key; } ;
typedef  TYPE_1__ zed_strings_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int
_zed_strings_node_compare(const void *x1, const void *x2)
{
	const char *s1;
	const char *s2;
	int rv;

	assert(x1 != NULL);
	assert(x2 != NULL);

	s1 = ((const zed_strings_node_t *) x1)->key;
	assert(s1 != NULL);
	s2 = ((const zed_strings_node_t *) x2)->key;
	assert(s2 != NULL);
	rv = strcmp(s1, s2);

	if (rv < 0)
		return (-1);

	if (rv > 0)
		return (1);

	return (0);
}