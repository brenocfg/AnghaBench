#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t len; size_t cap; int* data; } ;
typedef  TYPE_2__ uni_buf ;
typedef  int /*<<< orphan*/  fz_pool ;
struct TYPE_8__ {char* text; } ;
struct TYPE_10__ {int bidi_level; int type; struct TYPE_10__* next; TYPE_1__ content; } ;
typedef  TYPE_3__ fz_html_flow ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_bidi_direction ;
struct TYPE_11__ {TYPE_2__* buffer; TYPE_3__* flow; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_4__ bidi_data ;

/* Variables and functions */
#define  FLOW_BREAK 133 
#define  FLOW_IMAGE 132 
#define  FLOW_SBREAK 131 
#define  FLOW_SHYPHEN 130 
#define  FLOW_SPACE 129 
#define  FLOW_WORD 128 
 int /*<<< orphan*/  fragment_cb ; 
 int /*<<< orphan*/  fz_bidi_fragment_text (int /*<<< orphan*/ *,int*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_chartorune (int*,char const*) ; 
 int* fz_realloc_array (int /*<<< orphan*/ *,int*,size_t,int /*<<< orphan*/ ) ; 
 size_t fz_utflen (char*) ; 
 int /*<<< orphan*/  uint32_t ; 

__attribute__((used)) static fz_bidi_direction
detect_flow_directionality(fz_context *ctx, fz_pool *pool, uni_buf *buffer, fz_bidi_direction bidi_dir, fz_html_flow *flow)
{
	fz_html_flow *end = flow;
	bidi_data data;

	while (end)
	{
		int level = end->bidi_level;

		/* Gather the text from the flow up into a single buffer (at
		 * least, as much of it as has the same direction markup). */
		buffer->len = 0;
		while (end && (level & 1) == (end->bidi_level & 1))
		{
			size_t len = 0;
			const char *text = "";
			int broken = 0;

			switch (end->type)
			{
			case FLOW_WORD:
				len = fz_utflen(end->content.text);
				text = end->content.text;
				break;
			case FLOW_SPACE:
				len = 1;
				text = " ";
				break;
			case FLOW_SHYPHEN:
			case FLOW_SBREAK:
				break;
			case FLOW_BREAK:
			case FLOW_IMAGE:
				broken = 1;
				break;
			}

			end = end->next;

			if (broken)
				break;

			/* Make sure the buffer is large enough */
			if (buffer->len + len > buffer->cap)
			{
				size_t newcap = buffer->cap;
				if (newcap < 128)
					newcap = 128; /* Sensible small default */

				while (newcap < buffer->len + len)
					newcap = (newcap * 3) / 2;

				buffer->data = fz_realloc_array(ctx, buffer->data, newcap, uint32_t);
				buffer->cap = newcap;
			}

			/* Expand the utf8 text into Unicode and store it in the buffer */
			while (*text)
			{
				int rune;
				text += fz_chartorune(&rune, text);
				buffer->data[buffer->len++] = rune;
			}
		}

		/* Detect directionality for the buffer */
		data.ctx = ctx;
		data.pool = pool;
		data.flow = flow;
		data.buffer = buffer;
		fz_bidi_fragment_text(ctx, buffer->data, buffer->len, &bidi_dir, fragment_cb, &data, 0 /* Flags */);
		flow = end;
	}
	return bidi_dir;
}