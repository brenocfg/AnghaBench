#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char char_u ;
struct TYPE_13__ {int /*<<< orphan*/  norm_pixel; } ;
struct TYPE_12__ {int /*<<< orphan*/  x; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {void* y; void* x; } ;
struct TYPE_9__ {void* y; void* x; } ;
struct TYPE_11__ {TYPE_2__ lr; TYPE_1__ ul; } ;
typedef  TYPE_3__ PhRect_t ;
typedef  TYPE_4__ PhPoint_t ;

/* Variables and functions */
 int DRAW_BOLD ; 
 int /*<<< orphan*/  DRAW_END ; 
 int /*<<< orphan*/  DRAW_START ; 
 int DRAW_TRANSP ; 
 int DRAW_UNDERL ; 
 void* FILL_X (int) ; 
 void* FILL_Y (int) ; 
 int MB_LEN_MAX ; 
 int /*<<< orphan*/  PgDrawIRect (void*,void*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PgDrawText (char*,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PgDrawTextArea (char*,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PgSetUnderline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PgSetUserClip (TYPE_3__*) ; 
 int /*<<< orphan*/  Pg_DRAW_FILL ; 
 int /*<<< orphan*/  Pg_TEXT_BOTTOM ; 
 int /*<<< orphan*/  Pg_TRANSPARENT ; 
 int /*<<< orphan*/  PxTranslateToUTF (int /*<<< orphan*/ *,char*,int,int*,char*,int,int*) ; 
 int /*<<< orphan*/  TEXT_X (int) ; 
 int /*<<< orphan*/  TEXT_Y (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * charset_translate ; 
 scalar_t__ enc_utf8 ; 
 TYPE_5__ gui ; 
 scalar_t__ is_ignore_draw ; 
 int p_linespace ; 
 char* realloc (char*,int) ; 

void
gui_mch_draw_string(int row, int col, char_u *s, int len, int flags)
{
    static char *utf8_buffer = NULL;
    static int	utf8_len = 0;

    PhPoint_t	pos = { TEXT_X(col), TEXT_Y(row) };
    PhRect_t	rect;

    if (is_ignore_draw == TRUE)
	return;

    DRAW_START;

    if (!(flags & DRAW_TRANSP))
    {
	PgDrawIRect(
		FILL_X(col), FILL_Y(row),
		FILL_X(col + len) - 1, FILL_Y(row + 1) - 1,
		Pg_DRAW_FILL);
    }

    if (flags & DRAW_UNDERL)
	PgSetUnderline(gui.norm_pixel, Pg_TRANSPARENT, 0);

    if (charset_translate != NULL
#ifdef FEAT_MBYTE
	    && enc_utf8 == 0
#endif
	   )
    {
	int src_taken, dst_made;

	/* Use a static buffer to avoid large amounts of de/allocations */
	if (utf8_len < len)
	{
	    utf8_buffer = realloc(utf8_buffer, len * MB_LEN_MAX);
	    utf8_len = len;
	}

	PxTranslateToUTF(
		charset_translate,
		s,
		len,
		&src_taken,
		utf8_buffer,
		utf8_len,
		&dst_made);
	s = utf8_buffer;
	len = dst_made;
    }

    PgDrawText(s, len, &pos, 0);

    if (flags & DRAW_BOLD)
    {
	/* FIXME: try and only calculate these values once... */
	rect.ul.x = FILL_X(col) + 1;
	rect.ul.y = FILL_Y(row);
	rect.lr.x = FILL_X(col + len) - 1;
	rect.lr.y = FILL_Y(row + 1) - 1;
	/* PgSetUserClip(NULL) causes the scrollbar to not redraw... */
#if 0
	pos.x++;

	PgSetUserClip(&rect);
	PgDrawText(s, len, &pos, 0);
	PgSetUserClip(NULL);
#else
	rect.lr.y -= (p_linespace + 1) / 2;
	/* XXX: DrawTextArea doesn't work with phditto */
	PgDrawTextArea(s, len, &rect, Pg_TEXT_BOTTOM);
#endif
    }

    if (flags & DRAW_UNDERL)
	PgSetUnderline(Pg_TRANSPARENT, Pg_TRANSPARENT, 0);

    DRAW_END;
}