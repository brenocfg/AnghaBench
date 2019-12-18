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
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/ * create_list () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,char*) ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char const*) ; 

list_t *split_string(const char *str, const char *delims) {
	list_t *res = create_list();
	char *copy = strdup(str);

	char *token = strtok(copy, delims);
	while (token) {
		list_add(res, strdup(token));
		token = strtok(NULL, delims);
	}
	free(copy);
	return res;
}