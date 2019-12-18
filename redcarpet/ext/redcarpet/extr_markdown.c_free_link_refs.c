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
struct link_ref {int /*<<< orphan*/  title; int /*<<< orphan*/  link; struct link_ref* next; } ;

/* Variables and functions */
 size_t REF_TABLE_SIZE ; 
 int /*<<< orphan*/  bufrelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct link_ref*) ; 

__attribute__((used)) static void
free_link_refs(struct link_ref **references)
{
	size_t i;

	for (i = 0; i < REF_TABLE_SIZE; ++i) {
		struct link_ref *r = references[i];
		struct link_ref *next;

		while (r) {
			next = r->next;
			bufrelease(r->link);
			bufrelease(r->title);
			free(r);
			r = next;
		}
	}
}