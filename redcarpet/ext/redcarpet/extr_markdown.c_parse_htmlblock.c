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
struct TYPE_2__ {int /*<<< orphan*/  (* blockhtml ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {char* member_0; size_t size; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 char* find_block_tag (char*,int) ; 
 size_t htmlblock_end (char const*,struct sd_markdown*,char*,size_t,int) ; 
 size_t is_empty (char*,size_t) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
parse_htmlblock(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int do_render)
{
	size_t i, j = 0, tag_end;
	const char *curtag = NULL;
	struct buf work = { data, 0, 0, 0 };

	/* identification of the opening tag */
	if (size < 2 || data[0] != '<')
		return 0;

	i = 1;
	while (i < size && data[i] != '>' && data[i] != ' ')
		i++;

	if (i < size)
		curtag = find_block_tag((char *)data + 1, (int)i - 1);

	/* handling of special cases */
	if (!curtag) {

		/* HTML comment, laxist form */
		if (size > 5 && data[1] == '!' && data[2] == '-' && data[3] == '-') {
			i = 5;

			while (i < size && !(data[i - 2] == '-' && data[i - 1] == '-' && data[i] == '>'))
				i++;

			i++;

			if (i < size)
				j = is_empty(data + i, size - i);

			if (j) {
				work.size = i + j;
				if (do_render && rndr->cb.blockhtml)
					rndr->cb.blockhtml(ob, &work, rndr->opaque);
				return work.size;
			}
		}

		/* HR, which is the only self-closing block tag considered */
		if (size > 4 && (data[1] == 'h' || data[1] == 'H') && (data[2] == 'r' || data[2] == 'R')) {
			i = 3;
			while (i < size && data[i] != '>')
				i++;

			if (i + 1 < size) {
				i++;
				j = is_empty(data + i, size - i);
				if (j) {
					work.size = i + j;
					if (do_render && rndr->cb.blockhtml)
						rndr->cb.blockhtml(ob, &work, rndr->opaque);
					return work.size;
				}
			}
		}

		/* no special case recognised */
		return 0;
	}

	/* looking for an unindented matching closing tag */
	/*	followed by a blank line */
	tag_end = htmlblock_end(curtag, rndr, data, size, 1);

	/* if not found, trying a second pass looking for indented match */
	/* but not if tag is "ins" or "del" (following original Markdown.pl) */
	if (!tag_end && strcmp(curtag, "ins") != 0 && strcmp(curtag, "del") != 0) {
		tag_end = htmlblock_end(curtag, rndr, data, size, 0);
	}

	if (!tag_end)
		return 0;

	/* the end of the block has been found */
	work.size = tag_end;
	if (do_render && rndr->cb.blockhtml)
		rndr->cb.blockhtml(ob, &work, rndr->opaque);

	return tag_end;
}