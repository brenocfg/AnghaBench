#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_11__ {int left; int right; } ;
struct TYPE_14__ {int left_margin; int right_margin; TYPE_1__ format_rect; int /*<<< orphan*/  hwndSelf; scalar_t__ font; } ;
struct TYPE_13__ {int right; int left; } ;
struct TYPE_12__ {int tmPitchAndFamily; int /*<<< orphan*/  tmCharSet; } ;
typedef  TYPE_2__ TEXTMETRICW ;
typedef  TYPE_3__ RECT ;
typedef  int LONG ;
typedef  int INT ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_4__ EDITSTATE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int EC_LEFTMARGIN ; 
 int EC_RIGHTMARGIN ; 
 scalar_t__ EC_USEFONTINFO ; 
 int /*<<< orphan*/  EDIT_AdjustFormatRect (TYPE_4__*) ; 
 int /*<<< orphan*/  EDIT_UpdateText (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GdiGetCharDimensions (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsRectEmpty (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int TMPF_TRUETYPE ; 
 int TMPF_VECTOR ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_cjk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EDIT_EM_SetMargins(EDITSTATE *es, INT action,
			       WORD left, WORD right, BOOL repaint)
{
	TEXTMETRICW tm;
	INT default_left_margin  = 0; /* in pixels */
	INT default_right_margin = 0; /* in pixels */

        /* Set the default margins depending on the font */
        if (es->font && (left == EC_USEFONTINFO || right == EC_USEFONTINFO)) {
            HDC dc = GetDC(es->hwndSelf);
            HFONT old_font = SelectObject(dc, es->font);
            LONG width = GdiGetCharDimensions(dc, &tm, NULL);
            RECT rc;

            /* The default margins are only non zero for TrueType or Vector fonts */
            if (tm.tmPitchAndFamily & ( TMPF_VECTOR | TMPF_TRUETYPE )) {
                if (!is_cjk(tm.tmCharSet)) {
                    default_left_margin = width / 2;
                    default_right_margin = width / 2;

                    GetClientRect(es->hwndSelf, &rc);
                    if (rc.right - rc.left < (width / 2 + width) * 2 &&
                        (width >= 28 || !IsRectEmpty(&rc)) ) {
                        default_left_margin = es->left_margin;
                        default_right_margin = es->right_margin;
                    }
                } else {
                    /* FIXME: figure out the CJK values. They are not affected by the client rect. */
                    default_left_margin = width / 2;
                    default_right_margin = width / 2;
                }
            }
            SelectObject(dc, old_font);
            ReleaseDC(es->hwndSelf, dc);
        }

	if (action & EC_LEFTMARGIN) {
		es->format_rect.left -= es->left_margin;
		if (left != EC_USEFONTINFO)
			es->left_margin = left;
		else
			es->left_margin = default_left_margin;
		es->format_rect.left += es->left_margin;
	}

	if (action & EC_RIGHTMARGIN) {
		es->format_rect.right += es->right_margin;
		if (right != EC_USEFONTINFO)
			es->right_margin = right;
		else
			es->right_margin = default_right_margin;
		es->format_rect.right -= es->right_margin;
	}

	if (action & (EC_LEFTMARGIN | EC_RIGHTMARGIN)) {
		EDIT_AdjustFormatRect(es);
		if (repaint) EDIT_UpdateText(es, NULL, TRUE);
	}

	TRACE("left=%d, right=%d\n", es->left_margin, es->right_margin);
}