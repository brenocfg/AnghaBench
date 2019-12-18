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
typedef  char uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* quote ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {char* member_0; size_t member_1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
char_quote(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t offset, size_t size)
{
	size_t end, nq = 0, i, f_begin, f_end;

	/* counting the number of quotes in the delimiter */
	while (nq < size && data[nq] == '"')
		nq++;

	/* finding the next delimiter */
	i = 0;
	for (end = nq; end < size && i < nq; end++) {
		if (data[end] == '"') i++;
		else i = 0;
	}

	if (i < nq && end >= size)
		return 0; /* no matching delimiter */

	/* trimming outside whitespaces */
	f_begin = nq;
	while (f_begin < end && data[f_begin] == ' ')
		f_begin++;

	f_end = end - nq;
	while (f_end > nq && data[f_end-1] == ' ')
		f_end--;

	/* real quote */
	if (f_begin < f_end) {
		struct buf work = { data + f_begin, f_end - f_begin, 0, 0 };
		if (!rndr->cb.quote(ob, &work, rndr->opaque))
			end = 0;
	} else {
		if (!rndr->cb.quote(ob, 0, rndr->opaque))
			end = 0;
	}

	return end;
}