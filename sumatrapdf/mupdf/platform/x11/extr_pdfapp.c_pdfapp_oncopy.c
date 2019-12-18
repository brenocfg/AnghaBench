#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  selr; TYPE_4__* page_text; } ;
typedef  TYPE_3__ pdfapp_t ;
struct TYPE_16__ {TYPE_7__* first_block; } ;
typedef  TYPE_4__ fz_stext_page ;
struct TYPE_17__ {TYPE_6__* first_char; struct TYPE_17__* next; } ;
typedef  TYPE_5__ fz_stext_line ;
struct TYPE_18__ {int c; int /*<<< orphan*/  quad; struct TYPE_18__* next; } ;
typedef  TYPE_6__ fz_stext_char ;
struct TYPE_13__ {TYPE_5__* first_line; } ;
struct TYPE_14__ {TYPE_1__ t; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_2__ u; struct TYPE_19__* next; } ;
typedef  TYPE_7__ fz_stext_block ;
struct TYPE_20__ {scalar_t__ x1; scalar_t__ x0; scalar_t__ y1; scalar_t__ y0; } ;
typedef  TYPE_8__ fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;

/* Variables and functions */
 scalar_t__ FZ_STEXT_BLOCK_TEXT ; 
 int /*<<< orphan*/  fz_invert_matrix (int /*<<< orphan*/ ) ; 
 TYPE_8__ fz_rect_from_quad (int /*<<< orphan*/ ) ; 
 TYPE_8__ fz_transform_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdfapp_viewctm (int /*<<< orphan*/ *,TYPE_3__*) ; 

void pdfapp_oncopy(pdfapp_t *app, unsigned short *ucsbuf, int ucslen)
{
	fz_matrix ctm;
	fz_stext_page *page = app->page_text;
	int p, need_newline;
	fz_stext_block *block;
	fz_stext_line *line;
	fz_stext_char *ch;
	fz_rect sel;

	pdfapp_viewctm(&ctm, app);
	ctm = fz_invert_matrix(ctm);
	sel = fz_transform_rect(app->selr, ctm);

	p = 0;
	need_newline = 0;

	for (block = page->first_block; block; block = block->next)
	{
		if (block->type != FZ_STEXT_BLOCK_TEXT)
			continue;

		for (line = block->u.t.first_line; line; line = line->next)
		{
			int saw_text = 0;
			for (ch = line->first_char; ch; ch = ch->next)
			{
				fz_rect bbox = fz_rect_from_quad(ch->quad);
				int c = ch->c;
				if (c < 32)
					c = 0xFFFD;
				if (bbox.x1 >= sel.x0 && bbox.x0 <= sel.x1 && bbox.y1 >= sel.y0 && bbox.y0 <= sel.y1)
				{
					saw_text = 1;
					if (need_newline)
					{
#ifdef _WIN32
						if (p < ucslen - 1)
							ucsbuf[p++] = '\r';
#endif
						if (p < ucslen - 1)
							ucsbuf[p++] = '\n';
						need_newline = 0;
					}
					if (p < ucslen - 1)
						ucsbuf[p++] = c;
				}
			}
			if (saw_text)
				need_newline = 1;
		}
	}

	ucsbuf[p] = 0;
}