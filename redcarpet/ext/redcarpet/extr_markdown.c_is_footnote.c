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
typedef  char uint8_t ;
struct footnote_ref {struct buf* contents; } ;
struct footnote_list {int dummy; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_footnote_ref (struct footnote_list*,struct footnote_ref*) ; 
 struct buf* bufnew (int) ; 
 int /*<<< orphan*/  bufput (struct buf*,char const*,int) ; 
 int /*<<< orphan*/  bufputc (struct buf*,char) ; 
 struct footnote_ref* create_footnote_ref (struct footnote_list*,char const*,size_t) ; 
 int /*<<< orphan*/  free_footnote_ref (struct footnote_ref*) ; 
 scalar_t__ is_empty (char const*,size_t) ; 

__attribute__((used)) static int
is_footnote(const uint8_t *data, size_t beg, size_t end, size_t *last, struct footnote_list *list)
{
	size_t i = 0;
	struct buf *contents = 0;
	size_t ind = 0;
	int in_empty = 0;
	size_t start = 0;

	size_t id_offset, id_end;

	/* up to 3 optional leading spaces */
	if (beg + 3 >= end) return 0;
	if (data[beg] == ' ') { i = 1;
	if (data[beg + 1] == ' ') { i = 2;
	if (data[beg + 2] == ' ') { i = 3;
	if (data[beg + 3] == ' ') return 0; } } }
	i += beg;

	/* id part: caret followed by anything between brackets */
	if (data[i] != '[') return 0;
	i++;
	if (i >= end || data[i] != '^') return 0;
	i++;
	id_offset = i;
	while (i < end && data[i] != '\n' && data[i] != '\r' && data[i] != ']')
		i++;
	if (i >= end || data[i] != ']') return 0;
	id_end = i;

	/* spacer: colon (space | tab)* newline? (space | tab)* */
	i++;
	if (i >= end || data[i] != ':') return 0;
	i++;

	/* getting content buffer */
	contents = bufnew(64);

	start = i;

	/* process lines similiar to a list item */
	while (i < end) {
		while (i < end && data[i] != '\n' && data[i] != '\r') i++;

		/* process an empty line */
		if (is_empty(data + start, i - start)) {
			in_empty = 1;
			if (i < end && (data[i] == '\n' || data[i] == '\r')) {
				i++;
				if (i < end && data[i] == '\n' && data[i - 1] == '\r') i++;
			}
			start = i;
			continue;
		}

		/* calculating the indentation */
		ind = 0;
		while (ind < 4 && start + ind < end && data[start + ind] == ' ')
			ind++;

		/* joining only indented stuff after empty lines;
		 * note that now we only require 1 space of indentation
		 * to continue, just like lists */
		if (ind == 0) {
			if (start == id_end + 2 && data[start] == '\t') {}
			else break;
		}
		else if (in_empty) {
			bufputc(contents, '\n');
		}

		in_empty = 0;

		/* adding the line into the content buffer */
		bufput(contents, data + start + ind, i - start - ind);
		/* add carriage return */
		if (i < end) {
			bufput(contents, "\n", 1);
			if (i < end && (data[i] == '\n' || data[i] == '\r')) {
				i++;
				if (i < end && data[i] == '\n' && data[i - 1] == '\r') i++;
			}
		}
		start = i;
	}

	if (last)
		*last = start;

	if (list) {
		struct footnote_ref *ref;
		ref = create_footnote_ref(list, data + id_offset, id_end - id_offset);
		if (!ref)
			return 0;
		if (!add_footnote_ref(list, ref)) {
			free_footnote_ref(ref);
			return 0;
		}
		ref->contents = contents;
	}

	return 1;
}