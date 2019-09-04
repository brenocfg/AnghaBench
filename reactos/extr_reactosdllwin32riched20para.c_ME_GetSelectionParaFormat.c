#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int cbSize; int dwMask; scalar_t__ wNumbering; scalar_t__ dxStartIndent; scalar_t__ dxRightIndent; scalar_t__ dxOffset; scalar_t__ wAlignment; scalar_t__ cTabCount; int wEffects; scalar_t__ dySpaceBefore; scalar_t__ dySpaceAfter; scalar_t__ dyLineSpacing; scalar_t__ sStyle; scalar_t__ bLineSpacingRule; scalar_t__ wShadingWeight; scalar_t__ wShadingStyle; scalar_t__ wNumberingStart; scalar_t__ wNumberingStyle; scalar_t__ wNumberingTab; scalar_t__ wBorderSpace; scalar_t__ wBorderWidth; scalar_t__ wBorders; int /*<<< orphan*/  rgxTabs; } ;
struct TYPE_10__ {TYPE_3__ fmt; TYPE_4__* next_para; } ;
struct TYPE_11__ {TYPE_1__ para; } ;
struct TYPE_13__ {TYPE_2__ member; } ;
typedef  TYPE_3__ PARAFORMAT2 ;
typedef  int /*<<< orphan*/  PARAFORMAT ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_4__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  ME_GetParaFormat (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ME_GetSelectionParas (int /*<<< orphan*/ *,TYPE_4__**,TYPE_4__**) ; 
 int PFM_ALIGNMENT ; 
 int PFM_BORDER ; 
 int PFM_LINESPACING ; 
 int PFM_NUMBERING ; 
 int PFM_NUMBERINGSTART ; 
 int PFM_NUMBERINGSTYLE ; 
 int PFM_NUMBERINGTAB ; 
 int PFM_OFFSET ; 
 int PFM_RIGHTINDENT ; 
 int PFM_SHADING ; 
 int PFM_SPACEAFTER ; 
 int PFM_SPACEBEFORE ; 
 int PFM_STARTINDENT ; 
 int PFM_STYLE ; 
 int PFM_TABSTOPS ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ME_GetSelectionParaFormat(ME_TextEditor *editor, PARAFORMAT2 *pFmt)
{
  ME_DisplayItem *para, *para_end;
  PARAFORMAT2 *curFmt;

  if (pFmt->cbSize < sizeof(PARAFORMAT)) {
    pFmt->dwMask = 0;
    return;
  }

  ME_GetSelectionParas(editor, &para, &para_end);

  ME_GetParaFormat(editor, para, pFmt);

  /* Invalidate values that change across the selected paragraphs. */
  while (para != para_end)
  {
    para = para->member.para.next_para;
    curFmt = &para->member.para.fmt;

#define CHECK_FIELD(m, f) \
    if (pFmt->f != curFmt->f) pFmt->dwMask &= ~(m);

    CHECK_FIELD(PFM_NUMBERING, wNumbering);
    CHECK_FIELD(PFM_STARTINDENT, dxStartIndent);
    CHECK_FIELD(PFM_RIGHTINDENT, dxRightIndent);
    CHECK_FIELD(PFM_OFFSET, dxOffset);
    CHECK_FIELD(PFM_ALIGNMENT, wAlignment);
    if (pFmt->dwMask & PFM_TABSTOPS) {
      if (pFmt->cTabCount != para->member.para.fmt.cTabCount ||
          memcmp(pFmt->rgxTabs, curFmt->rgxTabs, curFmt->cTabCount*sizeof(int)))
        pFmt->dwMask &= ~PFM_TABSTOPS;
    }

    if (pFmt->dwMask >= sizeof(PARAFORMAT2))
    {
      pFmt->dwMask &= ~((pFmt->wEffects ^ curFmt->wEffects) << 16);
      CHECK_FIELD(PFM_SPACEBEFORE, dySpaceBefore);
      CHECK_FIELD(PFM_SPACEAFTER, dySpaceAfter);
      CHECK_FIELD(PFM_LINESPACING, dyLineSpacing);
      CHECK_FIELD(PFM_STYLE, sStyle);
      CHECK_FIELD(PFM_SPACEAFTER, bLineSpacingRule);
      CHECK_FIELD(PFM_SHADING, wShadingWeight);
      CHECK_FIELD(PFM_SHADING, wShadingStyle);
      CHECK_FIELD(PFM_NUMBERINGSTART, wNumberingStart);
      CHECK_FIELD(PFM_NUMBERINGSTYLE, wNumberingStyle);
      CHECK_FIELD(PFM_NUMBERINGTAB, wNumberingTab);
      CHECK_FIELD(PFM_BORDER, wBorderSpace);
      CHECK_FIELD(PFM_BORDER, wBorderWidth);
      CHECK_FIELD(PFM_BORDER, wBorders);
    }
#undef CHECK_FIELD
  }
}