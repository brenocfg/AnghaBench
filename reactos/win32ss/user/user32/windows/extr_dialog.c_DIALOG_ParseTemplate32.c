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
typedef  int WORD ;
typedef  int UINT_PTR ;
struct TYPE_3__ {int style; int nbItems; int x; int y; int cx; int cy; int pointSize; int weight; void* italic; int /*<<< orphan*/ * faceName; void* dialogEx; int /*<<< orphan*/ * caption; int /*<<< orphan*/ * className; int /*<<< orphan*/ * menuName; void* exStyle; void* helpId; } ;
typedef  void* LPCWSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  TYPE_1__ DLG_TEMPLATE ;

/* Variables and functions */
 int DS_SETFONT ; 
 void* FALSE ; 
 int FW_DONTCARE ; 
 void* GET_DWORD (int const*) ; 
 int GET_WORD (int const*) ; 
 void* LOBYTE (int) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 void* TRUE ; 
 int /*<<< orphan*/ * WC_DIALOG ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 scalar_t__ strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static LPCSTR DIALOG_ParseTemplate32( LPCSTR template, DLG_TEMPLATE * result )
{
    const WORD *p = (const WORD *)template;
    WORD signature;
    WORD dlgver;

    dlgver = GET_WORD(p); p++;
    signature = GET_WORD(p); p++;

    if (dlgver == 1 && signature == 0xffff)  /* DIALOGEX resource */
    {
        result->dialogEx = TRUE;
        result->helpId   = GET_DWORD(p); p += 2;
        result->exStyle  = GET_DWORD(p); p += 2;
        result->style    = GET_DWORD(p); p += 2;
    }
    else
    {
        result->style = GET_DWORD(p - 2);
        result->dialogEx = FALSE;
        result->helpId   = 0;
        result->exStyle  = GET_DWORD(p); p += 2;
    }
    result->nbItems = GET_WORD(p); p++;
    result->x       = GET_WORD(p); p++;
    result->y       = GET_WORD(p); p++;
    result->cx      = GET_WORD(p); p++;
    result->cy      = GET_WORD(p); p++;
    TRACE("DIALOG%s %d, %d, %d, %d, %d\n",
           result->dialogEx ? "EX" : "", result->x, result->y,
           result->cx, result->cy, result->helpId );
    TRACE(" STYLE 0x%08x\n", result->style );
    TRACE(" EXSTYLE 0x%08x\n", result->exStyle );

    /* Get the menu name */

    switch(GET_WORD(p))
    {
        case 0x0000:
            result->menuName = NULL;
            p++;
            break;
        case 0xffff:
            result->menuName = (LPCWSTR)(UINT_PTR)GET_WORD( p + 1 );
            p += 2;
            TRACE(" MENU %04x\n", LOWORD(result->menuName) );
            break;
        default:
            result->menuName = (LPCWSTR)p;
            TRACE(" MENU %s\n", debugstr_w(result->menuName) );
            p += strlenW( result->menuName ) + 1;
            break;
    }

    /* Get the class name */

    switch(GET_WORD(p))
    {
        case 0x0000:
            result->className = WC_DIALOG;
            p++;
            break;
        case 0xffff:
            result->className = (LPCWSTR)(UINT_PTR)GET_WORD( p + 1 );
            p += 2;
            TRACE(" CLASS %04x\n", LOWORD(result->className) );
            break;
        default:
            result->className = (LPCWSTR)p;
            TRACE(" CLASS %s\n", debugstr_w( result->className ));
            p += strlenW( result->className ) + 1;
            break;
    }

    /* Get the window caption */

    result->caption = (LPCWSTR)p;
    p += strlenW( result->caption ) + 1;
    TRACE(" CAPTION %s\n", debugstr_w( result->caption ) );

    /* Get the font name */

    result->pointSize = 0;
    result->faceName = NULL;
    result->weight = FW_DONTCARE;
    result->italic = FALSE;

    if (result->style & DS_SETFONT)
    {
        result->pointSize = GET_WORD(p);
        p++;

        /* If pointSize is 0x7fff, it means that we need to use the font
         * in NONCLIENTMETRICSW.lfMessageFont, and NOT read the weight,
         * italic, and facename from the dialog template.
         */
        if (result->pointSize == 0x7fff)
        {
            /* We could call SystemParametersInfo here, but then we'd have
             * to convert from pixel size to point size (which can be
             * imprecise).
             */
            TRACE(" FONT: Using message box font\n");
        }
        else
        {
            if (result->dialogEx)
            {
                result->weight = GET_WORD(p); p++;
                result->italic = LOBYTE(GET_WORD(p)); p++;
            }
            result->faceName = (LPCWSTR)p;
            p += strlenW( result->faceName ) + 1;

            TRACE(" FONT %d, %s, %d, %s\n",
                  result->pointSize, debugstr_w( result->faceName ),
                  result->weight, result->italic ? "TRUE" : "FALSE" );
        }
    }

    /* First control is on dword boundary */
    return (LPCSTR)((((UINT_PTR)p) + 3) & ~3);
}