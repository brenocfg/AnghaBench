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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int (* strikethrough ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;int (* highlight ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;int (* double_emphasis ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_SPAN ; 
 int /*<<< orphan*/  _isspace (scalar_t__) ; 
 size_t find_emph_char (scalar_t__*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  parse_inline (struct buf*,struct sd_markdown*,scalar_t__*,size_t) ; 
 struct buf* rndr_newbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndr_popbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int stub1 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 
 int stub2 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 
 int stub3 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
parse_emph2(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, uint8_t c)
{
	size_t i = 0, len;
	struct buf *work = 0;
	int r;

	while (i < size) {
		len = find_emph_char(data + i, size - i, c);
		if (!len) return 0;
		i += len;

		if (i + 1 < size && data[i] == c && data[i + 1] == c && i && !_isspace(data[i - 1])) {
			work = rndr_newbuf(rndr, BUFFER_SPAN);
			parse_inline(work, rndr, data, i);

			if (c == '~')
				r = rndr->cb.strikethrough(ob, work, rndr->opaque);
			else if (c == '=')
				r = rndr->cb.highlight(ob, work, rndr->opaque);
			else
				r = rndr->cb.double_emphasis(ob, work, rndr->opaque);

			rndr_popbuf(rndr, BUFFER_SPAN);
			return r ? i + 2 : 0;
		}
		i++;
	}
	return 0;
}