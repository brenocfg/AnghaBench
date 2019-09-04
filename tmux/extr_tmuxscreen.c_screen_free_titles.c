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
struct screen_title_entry {struct screen_title_entry* text; } ;
struct screen {struct screen_title_entry* titles; } ;

/* Variables and functions */
 struct screen_title_entry* TAILQ_FIRST (struct screen_title_entry*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct screen_title_entry*,struct screen_title_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct screen_title_entry*) ; 

__attribute__((used)) static void
screen_free_titles(struct screen *s)
{
	struct screen_title_entry	*title_entry;

	if (s->titles == NULL)
		return;

	while ((title_entry = TAILQ_FIRST(s->titles)) != NULL) {
		TAILQ_REMOVE(s->titles, title_entry, entry);
		free(title_entry->text);
		free(title_entry);
	}

	free(s->titles);
	s->titles = NULL;
}