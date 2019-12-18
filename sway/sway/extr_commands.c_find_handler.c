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
struct cmd_handler {char* command; } ;

/* Variables and functions */
 struct cmd_handler* bsearch (struct cmd_handler*,struct cmd_handler*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handler_compare ; 

struct cmd_handler *find_handler(char *line, struct cmd_handler *handlers,
		size_t handlers_size) {
	if (!handlers || !handlers_size) {
		return NULL;
	}
	struct cmd_handler query = { .command = line };
	return bsearch(&query, handlers,
			handlers_size / sizeof(struct cmd_handler),
			sizeof(struct cmd_handler), handler_compare);
}