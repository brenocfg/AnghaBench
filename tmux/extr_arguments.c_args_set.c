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
typedef  int /*<<< orphan*/  u_char ;
struct args_value {int /*<<< orphan*/  value; } ;
struct args_entry {int count; int /*<<< orphan*/  values; int /*<<< orphan*/  flag; } ;
struct args {int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct args_entry*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct args_value*,struct args_entry*) ; 
 struct args_entry* args_find (struct args*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  args_tree ; 
 void* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

void
args_set(struct args *args, u_char ch, const char *s)
{
	struct args_entry	*entry;
	struct args_value	*value;

	entry = args_find(args, ch);
	if (entry == NULL) {
		entry = xcalloc(1, sizeof *entry);
		entry->flag = ch;
		entry->count = 1;
		TAILQ_INIT(&entry->values);
		RB_INSERT(args_tree, &args->tree, entry);
	} else
		entry->count++;

	if (s != NULL) {
		value = xcalloc(1, sizeof *value);
		value->value = xstrdup(s);
		TAILQ_INSERT_TAIL(&entry->values, value, entry);
	}
}