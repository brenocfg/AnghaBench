#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_18__ {int dwMask; int dwEffects; } ;
struct TYPE_24__ {int /*<<< orphan*/  script_cache; TYPE_1__ fmt; } ;
struct TYPE_23__ {int /*<<< orphan*/  hDC; TYPE_2__* editor; } ;
struct TYPE_22__ {int /*<<< orphan*/  len; int /*<<< orphan*/  offsets; int /*<<< orphan*/  advances; int /*<<< orphan*/  num_glyphs; int /*<<< orphan*/  glyphs; int /*<<< orphan*/  script_analysis; TYPE_8__* style; TYPE_3__* para; } ;
struct TYPE_21__ {int /*<<< orphan*/ * szData; } ;
struct TYPE_20__ {int nFlags; } ;
struct TYPE_19__ {scalar_t__ cPasswordMask; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_4__ ME_String ;
typedef  TYPE_5__ ME_Run ;
typedef  TYPE_6__ ME_Context ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int BOOL ;

/* Variables and functions */
 int CFE_AUTOBACKCOLOR ; 
 int CFM_BACKCOLOR ; 
 int /*<<< orphan*/  ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOutW (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MEPF_COMPLEX ; 
 int /*<<< orphan*/  ME_DestroyString (TYPE_4__*) ; 
 TYPE_4__* ME_MakeStringR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScriptTextOut (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_underline (TYPE_6__*,TYPE_5__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_back_color (TYPE_6__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/ * get_text (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_text_color (TYPE_6__*,TYPE_8__*,int) ; 

__attribute__((used)) static void draw_text( ME_Context *c, ME_Run *run, int x, int y, BOOL selected, RECT *sel_rect )
{
    COLORREF text_color = get_text_color( c, run->style, selected );
    COLORREF back_color = get_back_color( c, run->style, selected );
    COLORREF old_text, old_back = 0;
    const WCHAR *text = get_text( run, 0 );
    ME_String *masked = NULL;
    const BOOL paint_bg = ( selected
        || ( ( run->style->fmt.dwMask & CFM_BACKCOLOR )
            && !(CFE_AUTOBACKCOLOR & run->style->fmt.dwEffects) )
        );

    if (c->editor->cPasswordMask)
    {
        masked = ME_MakeStringR( c->editor->cPasswordMask, run->len );
        text = masked->szData;
    }

    old_text = SetTextColor( c->hDC, text_color );
    if (paint_bg) old_back = SetBkColor( c->hDC, back_color );

    if (run->para->nFlags & MEPF_COMPLEX)
        ScriptTextOut( c->hDC, &run->style->script_cache, x, y, paint_bg ? ETO_OPAQUE : 0, sel_rect,
                       &run->script_analysis, NULL, 0, run->glyphs, run->num_glyphs, run->advances,
                       NULL, run->offsets );
    else
        ExtTextOutW( c->hDC, x, y, paint_bg ? ETO_OPAQUE : 0, sel_rect, text, run->len, NULL );

    if (paint_bg) SetBkColor( c->hDC, old_back );
    SetTextColor( c->hDC, old_text );

    draw_underline( c, run, x, y, text_color );

    ME_DestroyString( masked );
    return;
}