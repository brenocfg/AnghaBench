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
struct file_finder_line {scalar_t__ matches; } ;
struct TYPE_2__ {size_t lineno; } ;
struct file_finder {int lines; scalar_t__ searchlen; TYPE_1__ pos; struct file_finder_line** line; int /*<<< orphan*/  search; struct file_finder_line** file; } ;

/* Variables and functions */
 scalar_t__ file_finder_line_matches (struct file_finder_line*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct file_finder_line**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
file_finder_update(struct file_finder *finder)
{
	struct file_finder_line *current = finder->line[finder->pos.lineno];
	size_t new_lineno = 0;
	int i;

	memset(finder->line, 0, sizeof(*finder->line) * finder->lines);
	finder->lines = 0;

	for (i = 0; finder->file && finder->file[i]; i++) {
		struct file_finder_line *line = finder->file[i];

		if (line == current)
			current = NULL;

		if (line->matches + 1 < finder->searchlen) {
			continue;
		}

		if (line->matches >= finder->searchlen) {
			line->matches = finder->searchlen;
		} else {
			line->matches = file_finder_line_matches(line, finder->search);
			if (line->matches < finder->searchlen)
				continue;
		}

		if (current != NULL)
			new_lineno++;

		finder->line[finder->lines++] = line;
	}

	finder->pos.lineno = new_lineno;
}