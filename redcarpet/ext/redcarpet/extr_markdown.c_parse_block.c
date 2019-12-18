#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* hrule ) (struct buf*,int /*<<< orphan*/ ) ;scalar_t__ blockhtml; } ;
struct sd_markdown {scalar_t__ max_nesting; int ext_flags; int /*<<< orphan*/  opaque; TYPE_2__ cb; TYPE_1__* work_bufs; } ;
struct buf {int dummy; } ;
struct TYPE_3__ {scalar_t__ size; } ;

/* Variables and functions */
 size_t BUFFER_BLOCK ; 
 size_t BUFFER_SPAN ; 
 int MKDEXT_DISABLE_INDENTED_CODE ; 
 int MKDEXT_FENCED_CODE ; 
 int MKDEXT_TABLES ; 
 int /*<<< orphan*/  MKD_LIST_ORDERED ; 
 scalar_t__ is_atxheader (struct sd_markdown*,char*,size_t) ; 
 size_t is_empty (char*,size_t) ; 
 scalar_t__ is_hrule (char*,size_t) ; 
 scalar_t__ parse_atxheader (struct buf*,struct sd_markdown*,char*,size_t) ; 
 scalar_t__ parse_blockcode (struct buf*,struct sd_markdown*,char*,size_t) ; 
 scalar_t__ parse_blockquote (struct buf*,struct sd_markdown*,char*,size_t) ; 
 size_t parse_fencedcode (struct buf*,struct sd_markdown*,char*,size_t) ; 
 size_t parse_htmlblock (struct buf*,struct sd_markdown*,char*,size_t,int) ; 
 scalar_t__ parse_list (struct buf*,struct sd_markdown*,char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_paragraph (struct buf*,struct sd_markdown*,char*,size_t) ; 
 size_t parse_table (struct buf*,struct sd_markdown*,char*,size_t) ; 
 scalar_t__ prefix_code (char*,size_t) ; 
 scalar_t__ prefix_oli (char*,size_t) ; 
 scalar_t__ prefix_quote (char*,size_t) ; 
 scalar_t__ prefix_uli (char*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_block(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
	size_t beg, end, i;
	uint8_t *txt_data;
	beg = 0;

	if (rndr->work_bufs[BUFFER_SPAN].size +
		rndr->work_bufs[BUFFER_BLOCK].size > rndr->max_nesting)
		return;

	while (beg < size) {
		txt_data = data + beg;
		end = size - beg;

		if (is_atxheader(rndr, txt_data, end))
			beg += parse_atxheader(ob, rndr, txt_data, end);

		else if (data[beg] == '<' && rndr->cb.blockhtml &&
				(i = parse_htmlblock(ob, rndr, txt_data, end, 1)) != 0)
			beg += i;

		else if ((i = is_empty(txt_data, end)) != 0)
			beg += i;

		else if (is_hrule(txt_data, end)) {
			if (rndr->cb.hrule)
				rndr->cb.hrule(ob, rndr->opaque);

			while (beg < size && data[beg] != '\n')
				beg++;

			beg++;
		}

		else if ((rndr->ext_flags & MKDEXT_FENCED_CODE) != 0 &&
			(i = parse_fencedcode(ob, rndr, txt_data, end)) != 0)
			beg += i;

		else if ((rndr->ext_flags & MKDEXT_TABLES) != 0 &&
			(i = parse_table(ob, rndr, txt_data, end)) != 0)
			beg += i;

		else if (prefix_quote(txt_data, end))
			beg += parse_blockquote(ob, rndr, txt_data, end);

		else if (!(rndr->ext_flags & MKDEXT_DISABLE_INDENTED_CODE) && prefix_code(txt_data, end))
			beg += parse_blockcode(ob, rndr, txt_data, end);

		else if (prefix_uli(txt_data, end))
			beg += parse_list(ob, rndr, txt_data, end, 0);

		else if (prefix_oli(txt_data, end))
			beg += parse_list(ob, rndr, txt_data, end, MKD_LIST_ORDERED);

		else
			beg += parse_paragraph(ob, rndr, txt_data, end);
	}
}