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
struct string_map {char* (* key_fn ) (void const*) ;int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* stub1 (void const*) ; 

__attribute__((used)) static int
string_map_equal(const void *element, const void *map_)
{
	struct string_map *map = (struct string_map *) map_;
	const char *key = map->key_fn(element);

	return !strcmp(key, map->key);
}