#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int wState; scalar_t__ hWndLBox; scalar_t__ hWndEdit; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ HEADCOMBO ;

/* Variables and functions */
 int CBF_EDIT ; 
 int /*<<< orphan*/  LB_ERR ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  LB_GETTEXTLEN ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_GETTEXT ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpynW (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT COMBO_GetText( HEADCOMBO *lphc, INT count, LPWSTR buf )
{
    INT length;

    if( lphc->wState & CBF_EDIT )
        return SendMessageW( lphc->hWndEdit, WM_GETTEXT, count, (LPARAM)buf );

    /* get it from the listbox */

    if (!count || !buf) return 0;
    if( lphc->hWndLBox )
    {
        INT idx = SendMessageW(lphc->hWndLBox, LB_GETCURSEL, 0, 0);
        if (idx == LB_ERR) goto error;
        length = SendMessageW(lphc->hWndLBox, LB_GETTEXTLEN, idx, 0 );
        if (length == LB_ERR) goto error;

        /* 'length' is without the terminating character */
        if (length >= count)
        {
            WCHAR *lpBuffer = heap_alloc((length + 1) * sizeof(WCHAR));
            if (!lpBuffer) goto error;
            length = SendMessageW(lphc->hWndLBox, LB_GETTEXT, idx, (LPARAM)lpBuffer);

            /* truncate if buffer is too short */
            if (length != LB_ERR)
            {
                lstrcpynW( buf, lpBuffer, count );
                length = count;
            }
            heap_free( lpBuffer );
        }
        else length = SendMessageW(lphc->hWndLBox, LB_GETTEXT, idx, (LPARAM)buf);

        if (length == LB_ERR) return 0;
        return length;
    }

 error:  /* error - truncate string, return zero */
    buf[0] = 0;
    return 0;
}