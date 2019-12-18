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
struct TYPE_2__ {int (* underline ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;int (* emphasis ) (struct buf*,struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int ext_flags; int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_SPAN ; 
 int MKDEXT_NO_INTRA_EMPHASIS ; 
 int MKDEXT_UNDERLINE ; 
 scalar_t__ _isalnum (char) ; 
 int /*<<< orphan*/  _isspace (char) ; 
 size_t find_emph_char (char*,size_t,char) ; 
 int /*<<< orphan*/  parse_inline (struct buf*,struct sd_markdown*,char*,size_t) ; 
 struct buf* rndr_newbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rndr_popbuf (struct sd_markdown*,int /*<<< orphan*/ ) ; 
 int stub1 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 
 int stub2 (struct buf*,struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
parse_emph1(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, uint8_t c)
{
	size_t i = 0, len;
	struct buf *work = 0;
	int r;

	/* skipping one symbol if coming from emph3 */
	if (size > 1 && data[0] == c && data[1] == c) i = 1;

	while (i < size) {
		len = find_emph_char(data + i, size - i, c);
		if (!len) return 0;
		i += len;
		if (i >= size) return 0;

		if (data[i] == c && !_isspace(data[i - 1])) {

			if (rndr->ext_flags & MKDEXT_NO_INTRA_EMPHASIS) {
				if (i + 1 < size && _isalnum(data[i + 1]))
					continue;
			}

			work = rndr_newbuf(rndr, BUFFER_SPAN);
			parse_inline(work, rndr, data, i);

			if (rndr->ext_flags & MKDEXT_UNDERLINE && c == '_')
				r = rndr->cb.underline(ob, work, rndr->opaque);
			else
				r = rndr->cb.emphasis(ob, work, rndr->opaque);

			rndr_popbuf(rndr, BUFFER_SPAN);
			return r ? i + 1 : 0;
		}
	}

	return 0;
}