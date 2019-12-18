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
struct key_mapping {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct key_mapping const*) ; 
 struct key_mapping const* key_mappings ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static const struct key_mapping *
get_key_mapping(const char *name, size_t namelen)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(key_mappings); i++) {
		if (namelen == strlen(key_mappings[i].name) &&
		    !strncasecmp(key_mappings[i].name, name, namelen))
			return &key_mappings[i];
	}

	return NULL;
}