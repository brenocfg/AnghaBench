#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  char WCHAR ;
struct TYPE_5__ {int style; char* text; int /*<<< orphan*/  bound; } ;
struct TYPE_4__ {int numParts; int /*<<< orphan*/  Self; TYPE_2__* parts; TYPE_2__ part0; } ;
typedef  TYPE_1__ STATUS_INFO ;
typedef  TYPE_2__ STATUSWINDOWPART ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int INT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 char* Alloc (int) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int SBT_OWNERDRAW ; 
 int /*<<< orphan*/  TRACE (char*,int,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 char* debugstr_t (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isprintW (char) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 
 int strlenW (char*) ; 

__attribute__((used)) static BOOL
STATUSBAR_SetTextT (STATUS_INFO *infoPtr, INT nPart, WORD style,
		    LPWSTR text, BOOL isW)
{
    STATUSWINDOWPART *part=NULL;
    BOOL changed = FALSE;
    INT  oldStyle;

    if (style & SBT_OWNERDRAW) {
         TRACE("part %d, text %p\n",nPart,text);
    }
    else TRACE("part %d, text %s\n", nPart, debugstr_t(text, isW));

    /* MSDN says: "If the parameter is set to SB_SIMPLEID (255), the status
     * window is assumed to be a simple window */

    if (nPart == 0x00ff) {
	part = &infoPtr->part0;
    } else {
	if (infoPtr->parts && nPart >= 0 && nPart < infoPtr->numParts) {
	    part = &infoPtr->parts[nPart];
	}
    }
    if (!part) return FALSE;

    if (part->style != style)
	changed = TRUE;

    oldStyle = part->style;
    part->style = style;
    if (style & SBT_OWNERDRAW) {
        if (!(oldStyle & SBT_OWNERDRAW))
            Free (part->text);
        part->text = text;
    } else {
	LPWSTR ntext;
	WCHAR  *idx;

	if (text && !isW) {
	    LPCSTR atxt = (LPCSTR)text;
            DWORD len = MultiByteToWideChar( CP_ACP, 0, atxt, -1, NULL, 0 );
	    ntext = Alloc( (len + 1)*sizeof(WCHAR) );
	    if (!ntext) return FALSE;
            MultiByteToWideChar( CP_ACP, 0, atxt, -1, ntext, len );
	} else if (text) {
	    ntext = Alloc( (strlenW(text) + 1)*sizeof(WCHAR) );
	    if (!ntext) return FALSE;
	    strcpyW (ntext, text);
	} else ntext = 0;

	/* replace nonprintable characters with spaces */
	if (ntext) {
	    idx = ntext;
	    while (*idx) {
	        if(!isprintW(*idx))
	            *idx = ' ';
	        idx++;
	    }
	}

	/* check if text is unchanged -> no need to redraw */
	if (text) {
	    if (!changed && part->text && !lstrcmpW(ntext, part->text)) {
		Free(ntext);
		return TRUE;
	    }
	} else {
	    if (!changed && !part->text)
		return TRUE;
	}

	if (!(oldStyle & SBT_OWNERDRAW))
	    Free (part->text);
	part->text = ntext;
    }
    InvalidateRect(infoPtr->Self, &part->bound, FALSE);
    UpdateWindow(infoPtr->Self);

    return TRUE;
}