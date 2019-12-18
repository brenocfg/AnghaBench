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
typedef  int /*<<< orphan*/  uint8_t ;
struct buf {int dummy; } ;
typedef  int /*<<< orphan*/  ent ;

/* Variables and functions */
 int /*<<< orphan*/  bufputs (struct buf*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  word_boundary (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smartypants_quotes(struct buf *ob, uint8_t previous_char, uint8_t next_char, uint8_t quote, int *is_open)
{
	char ent[8];

	if (*is_open && !word_boundary(next_char))
		return 0;

	if (!(*is_open) && !word_boundary(previous_char))
		return 0;

	snprintf(ent, sizeof(ent), "&%c%cquo;", (*is_open) ? 'r' : 'l', quote);
	*is_open = !(*is_open);
	bufputs(ob, ent);
	return 1;
}