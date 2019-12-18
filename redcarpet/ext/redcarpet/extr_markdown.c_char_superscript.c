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
struct TYPE_2__ {int /*<<< orphan*/  (* superscript ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_SPAN ; 
 int /*<<< orphan*/  _isspace (char) ; 
 int /*<<< orphan*/  parse_inline (struct buf*,struct sd_markdown*,char*,size_t) ; 
 struct buf* rndr_newbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndr_popbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
char_superscript(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t offset, size_t size)
{
	size_t sup_start, sup_len;
	struct buf *sup;

	if (!rndr->cb.superscript)
		return 0;

	if (size < 2)
		return 0;

	if (data[1] == '(') {
		sup_start = sup_len = 2;

		while (sup_len < size && data[sup_len] != ')' && data[sup_len - 1] != '\\')
			sup_len++;

		if (sup_len == size)
			return 0;
	} else {
		sup_start = sup_len = 1;

		while (sup_len < size && !_isspace(data[sup_len]))
			sup_len++;
	}

	if (sup_len - sup_start == 0)
		return (sup_start == 2) ? 3 : 0;

	sup = rndr_newbuf(rndr, BUFFER_SPAN);
	parse_inline(sup, rndr, data + sup_start, sup_len - sup_start);
	rndr->cb.superscript(ob, sup, rndr->opaque);
	rndr_popbuf(rndr, BUFFER_SPAN);

	return (sup_start == 2) ? sup_len + 1 : sup_len;
}