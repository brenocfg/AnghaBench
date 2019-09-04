#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* editor; } ;
struct TYPE_8__ {int dwMask; int dwEffects; int /*<<< orphan*/  crBackColor; } ;
struct TYPE_9__ {TYPE_2__ fmt; } ;
struct TYPE_7__ {int /*<<< orphan*/  texthost; } ;
typedef  TYPE_3__ ME_Style ;
typedef  TYPE_4__ ME_Context ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CFE_AUTOBACKCOLOR ; 
 int CFM_BACKCOLOR ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHT ; 
 int /*<<< orphan*/  COLOR_WINDOW ; 
 int /*<<< orphan*/  ITextHost_TxGetSysColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static COLORREF get_back_color( ME_Context *c, ME_Style *style, BOOL highlight )
{
    COLORREF color;

    if (highlight)
        color = ITextHost_TxGetSysColor( c->editor->texthost, COLOR_HIGHLIGHT );
    else if ( (style->fmt.dwMask & CFM_BACKCOLOR)
            && !(style->fmt.dwEffects & CFE_AUTOBACKCOLOR) )
        color = style->fmt.crBackColor;
    else
        color = ITextHost_TxGetSysColor( c->editor->texthost, COLOR_WINDOW );

    return color;
}