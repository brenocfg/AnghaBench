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
struct input_table_entry {scalar_t__ ch; int /*<<< orphan*/  interm; } ;
struct input_ctx {scalar_t__ ch; int /*<<< orphan*/  interm_buf; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
input_table_compare(const void *key, const void *value)
{
	const struct input_ctx		*ictx = key;
	const struct input_table_entry	*entry = value;

	if (ictx->ch != entry->ch)
		return (ictx->ch - entry->ch);
	return (strcmp(ictx->interm_buf, entry->interm));
}