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
struct screen_title_entry {int /*<<< orphan*/  text; } ;
struct screen {int /*<<< orphan*/ * titles; int /*<<< orphan*/  title; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct screen_title_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 void* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

void
screen_push_title(struct screen *s)
{
	struct screen_title_entry *title_entry;

	if (s->titles == NULL) {
		s->titles = xmalloc(sizeof *s->titles);
		TAILQ_INIT(s->titles);
	}
	title_entry = xmalloc(sizeof *title_entry);
	title_entry->text = xstrdup(s->title);
	TAILQ_INSERT_HEAD(s->titles, title_entry, entry);
}