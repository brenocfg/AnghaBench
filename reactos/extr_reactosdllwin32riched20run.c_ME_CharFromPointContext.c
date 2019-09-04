#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_26__ {int /*<<< orphan*/  fLogicalOrder; int /*<<< orphan*/  fRTL; } ;
struct TYPE_25__ {int /*<<< orphan*/  hDC; TYPE_2__* editor; } ;
struct TYPE_24__ {int len; int nFlags; int nWidth; int /*<<< orphan*/  style; TYPE_8__ script_analysis; int /*<<< orphan*/  advances; int /*<<< orphan*/  vis_attrs; int /*<<< orphan*/  clusters; int /*<<< orphan*/  num_glyphs; TYPE_1__* para; } ;
struct TYPE_23__ {int /*<<< orphan*/ * szData; } ;
struct TYPE_22__ {int cx; } ;
struct TYPE_21__ {scalar_t__ cPasswordMask; } ;
struct TYPE_20__ {int nFlags; } ;
typedef  TYPE_3__ SIZE ;
typedef  TYPE_4__ ME_String ;
typedef  TYPE_5__ ME_Run ;
typedef  TYPE_6__ ME_Context ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetTextExtentExPointW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int MEPF_COMPLEX ; 
 int MERF_ENDCELL ; 
 int MERF_GRAPHICS ; 
 int MERF_TAB ; 
 int /*<<< orphan*/  ME_DestroyString (TYPE_4__*) ; 
 int /*<<< orphan*/  ME_GetOLEObjectSize (TYPE_6__*,TYPE_5__*,TYPE_3__*) ; 
 TYPE_4__* ME_MakeStringR (scalar_t__,int) ; 
 int /*<<< orphan*/  ME_SelectStyleFont (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_UnselectStyleFont (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScriptXtoCP (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int*,int*) ; 
 int /*<<< orphan*/  TRACE (char*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_text (TYPE_5__*,int /*<<< orphan*/ ) ; 

int ME_CharFromPointContext(ME_Context *c, int cx, ME_Run *run, BOOL closest, BOOL visual_order)
{
  ME_String *mask_text = NULL;
  WCHAR *str;
  int fit = 0;
  HGDIOBJ hOldFont;
  SIZE sz, sz2, sz3;
  if (!run->len || cx <= 0)
    return 0;

  if (run->nFlags & (MERF_TAB | MERF_ENDCELL))
  {
    if (!closest || cx < run->nWidth / 2) return 0;
    return 1;
  }

  if (run->nFlags & MERF_GRAPHICS)
  {
    SIZE sz;
    ME_GetOLEObjectSize(c, run, &sz);
    if (!closest || cx < sz.cx / 2) return 0;
    return 1;
  }

  if (run->para->nFlags & MEPF_COMPLEX)
  {
      int cp, trailing;
      if (visual_order && run->script_analysis.fRTL) cx = run->nWidth - cx - 1;

      ScriptXtoCP( cx, run->len, run->num_glyphs, run->clusters, run->vis_attrs, run->advances, &run->script_analysis,
                   &cp, &trailing );
      TRACE("x %d cp %d trailing %d (run width %d) rtl %d log order %d\n", cx, cp, trailing, run->nWidth,
            run->script_analysis.fRTL, run->script_analysis.fLogicalOrder);
      return closest ? cp + trailing : cp;
  }

  if (c->editor->cPasswordMask)
  {
    mask_text = ME_MakeStringR( c->editor->cPasswordMask, run->len );
    str = mask_text->szData;
  }
  else
    str = get_text( run, 0 );

  hOldFont = ME_SelectStyleFont(c, run->style);
  GetTextExtentExPointW(c->hDC, str, run->len,
                        cx, &fit, NULL, &sz);
  if (closest && fit != run->len)
  {
    GetTextExtentPoint32W(c->hDC, str, fit, &sz2);
    GetTextExtentPoint32W(c->hDC, str, fit + 1, &sz3);
    if (cx >= (sz2.cx+sz3.cx)/2)
      fit = fit + 1;
  }

  ME_DestroyString( mask_text );

  ME_UnselectStyleFont(c, run->style, hOldFont);
  return fit;
}