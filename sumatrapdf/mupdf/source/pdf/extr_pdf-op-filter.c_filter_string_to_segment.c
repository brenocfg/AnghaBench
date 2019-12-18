#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  encoding; } ;
typedef  TYPE_3__ pdf_font_desc ;
struct TYPE_13__ {TYPE_5__* gstate; } ;
typedef  TYPE_4__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_10__ {int /*<<< orphan*/  word_space; TYPE_3__* font; } ;
struct TYPE_11__ {TYPE_1__ text; } ;
struct TYPE_14__ {TYPE_2__ pending; } ;
typedef  TYPE_5__ filter_gstate ;

/* Variables and functions */
 int FZ_REPLACEMENT_CHARACTER ; 
 int filter_show_char (int /*<<< orphan*/ *,TYPE_4__*,int,int*) ; 
 int /*<<< orphan*/  filter_show_space (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mcid_char (int /*<<< orphan*/ *,TYPE_4__*,int,int) ; 
 int pdf_decode_cmap (int /*<<< orphan*/ ,unsigned char*,unsigned char*,unsigned int*) ; 
 int pdf_lookup_cmap (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
filter_string_to_segment(fz_context *ctx, pdf_filter_processor *p, unsigned char *buf, int len, int *pos, int *inc, int *removed_space)
{
	filter_gstate *gstate = p->gstate;
	pdf_font_desc *fontdesc = gstate->pending.text.font;
	unsigned char *end = buf + len;
	unsigned int cpt;
	int cid;
	int remove;

	buf += *pos;

	*removed_space = 0;

	while (buf < end)
	{
		int uni;
		*inc = pdf_decode_cmap(fontdesc->encoding, buf, end, &cpt);
		buf += *inc;

		cid = pdf_lookup_cmap(fontdesc->encoding, cpt);
		if (cid < 0)
		{
			uni = FZ_REPLACEMENT_CHARACTER;
			fz_warn(ctx, "cannot encode character");
		}
		else
			remove = filter_show_char(ctx, p, cid, &uni);
		if (cpt == 32 && *inc == 1)
			filter_show_space(ctx, p, gstate->pending.text.word_space);
		/* For every character we process (whether we remove it
		 * or not), we consider any MCIDs that are in effect. */
		mcid_char(ctx, p, uni, remove);
		if (remove)
		{
			*removed_space = (cpt == 32 && *inc == 1);
			return;
		}
		*pos += *inc;
	}
}