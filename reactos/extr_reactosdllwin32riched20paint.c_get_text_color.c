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
struct TYPE_10__ {TYPE_2__* editor; } ;
struct TYPE_7__ {int dwMask; int dwEffects; int /*<<< orphan*/  crTextColor; } ;
struct TYPE_9__ {TYPE_1__ fmt; } ;
struct TYPE_8__ {int /*<<< orphan*/  texthost; } ;
typedef  TYPE_3__ ME_Style ;
typedef  TYPE_4__ ME_Context ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CFE_AUTOCOLOR ; 
 int CFE_LINK ; 
 int CFM_COLOR ; 
 int CFM_LINK ; 
 int /*<<< orphan*/  COLOR_HIGHLIGHTTEXT ; 
 int /*<<< orphan*/  COLOR_WINDOWTEXT ; 
 int /*<<< orphan*/  ITextHost_TxGetSysColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static COLORREF get_text_color( ME_Context *c, ME_Style *style, BOOL highlight )
{
    COLORREF color;

    if (highlight)
        color = ITextHost_TxGetSysColor( c->editor->texthost, COLOR_HIGHLIGHTTEXT );
    else if ((style->fmt.dwMask & CFM_LINK) && (style->fmt.dwEffects & CFE_LINK))
        color = RGB(0,0,255);
    else if ((style->fmt.dwMask & CFM_COLOR) && (style->fmt.dwEffects & CFE_AUTOCOLOR))
        color = ITextHost_TxGetSysColor( c->editor->texthost, COLOR_WINDOWTEXT );
    else
        color = style->fmt.crTextColor;

    return color;
}