#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fmt ;
struct TYPE_7__ {int cbSize; int dwMask; scalar_t__ wWeight; scalar_t__ sSpacing; void* yHeight; void* yOffset; int /*<<< orphan*/  szFaceName; scalar_t__ lcid; void* wKerning; scalar_t__ crTextColor; int /*<<< orphan*/  dwEffects; scalar_t__ crBackColor; scalar_t__ bAnimation; } ;
struct TYPE_6__ {int /*<<< orphan*/  editor; } ;
typedef  int /*<<< orphan*/  ME_Cursor ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  ITextRange ;
typedef  int /*<<< orphan*/  ITextFont ;
typedef  TYPE_1__ IRichEditOleImpl ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ FLOAT ;
typedef  TYPE_2__ CHARFORMAT2W ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFE_ALLCAPS ; 
 int /*<<< orphan*/  CFE_AUTOBACKCOLOR ; 
 int /*<<< orphan*/  CFE_AUTOCOLOR ; 
 int /*<<< orphan*/  CFE_BOLD ; 
 int /*<<< orphan*/  CFE_EMBOSS ; 
 int /*<<< orphan*/  CFE_HIDDEN ; 
 int /*<<< orphan*/  CFE_IMPRINT ; 
 int /*<<< orphan*/  CFE_ITALIC ; 
 int /*<<< orphan*/  CFE_OUTLINE ; 
 int /*<<< orphan*/  CFE_PROTECTED ; 
 int /*<<< orphan*/  CFE_SHADOW ; 
 int /*<<< orphan*/  CFE_SMALLCAPS ; 
 int /*<<< orphan*/  CFE_STRIKEOUT ; 
 int /*<<< orphan*/  CFE_SUBSCRIPT ; 
 int /*<<< orphan*/  CFE_SUPERSCRIPT ; 
 int /*<<< orphan*/  CFE_UNDERLINE ; 
 int CFM_ALLCAPS ; 
 int CFM_ANIMATION ; 
 int CFM_BACKCOLOR ; 
 int CFM_BOLD ; 
 int CFM_COLOR ; 
 int CFM_EMBOSS ; 
 int CFM_FACE ; 
 int CFM_HIDDEN ; 
 int CFM_IMPRINT ; 
 int CFM_ITALIC ; 
 int CFM_KERNING ; 
 int CFM_LCID ; 
 int CFM_OFFSET ; 
 int CFM_OUTLINE ; 
 int CFM_PROTECTED ; 
 int CFM_SHADOW ; 
 int CFM_SIZE ; 
 int CFM_SMALLCAPS ; 
 int CFM_SPACING ; 
 int CFM_STRIKEOUT ; 
 int CFM_SUBSCRIPT ; 
 int CFM_SUPERSCRIPT ; 
 int CFM_UNDERLINE ; 
 int CFM_WEIGHT ; 
 scalar_t__ ITextFont_GetAllCaps (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetAnimation (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetBackColor (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetBold (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetEmboss (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetEngrave (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetForeColor (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetHidden (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetItalic (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetKerning (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetLanguageID (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ITextFont_GetOutline (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetPosition (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetProtected (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetShadow (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetSize (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetSmallCaps (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetSpacing (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetStrikeThrough (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetSubscript (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetSuperscript (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetUnderline (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ITextFont_GetWeight (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ITextRange_GetEnd (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ITextRange_GetStart (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ME_CursorFromCharOfs (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_SetCharFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_range_reole (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 void* points_to_twips (scalar_t__) ; 
 scalar_t__ tomAutoColor ; 
 scalar_t__ tomTrue ; 
 scalar_t__ tomUndefined ; 

__attribute__((used)) static void textrange_set_font(ITextRange *range, ITextFont *font)
{
    CHARFORMAT2W fmt;
    HRESULT hr;
    LONG value;
    BSTR str;
    FLOAT f;

#define CHARFORMAT_SET_B_FIELD(mask, value) \
    if (hr == S_OK && value != tomUndefined) { \
        fmt.dwMask |= CFM_##mask; \
        if (value == tomTrue) fmt.dwEffects |= CFE_##mask; \
    } \

    /* fill format data from font */
    memset(&fmt, 0, sizeof(fmt));
    fmt.cbSize = sizeof(fmt);

    value = tomUndefined;
    hr = ITextFont_GetAllCaps(font, &value);
    CHARFORMAT_SET_B_FIELD(ALLCAPS, value);

    value = tomUndefined;
    hr = ITextFont_GetBold(font, &value);
    CHARFORMAT_SET_B_FIELD(BOLD, value);

    value = tomUndefined;
    hr = ITextFont_GetEmboss(font, &value);
    CHARFORMAT_SET_B_FIELD(EMBOSS, value);

    value = tomUndefined;
    hr = ITextFont_GetHidden(font, &value);
    CHARFORMAT_SET_B_FIELD(HIDDEN, value);

    value = tomUndefined;
    hr = ITextFont_GetEngrave(font, &value);
    CHARFORMAT_SET_B_FIELD(IMPRINT, value);

    value = tomUndefined;
    hr = ITextFont_GetItalic(font, &value);
    CHARFORMAT_SET_B_FIELD(ITALIC, value);

    value = tomUndefined;
    hr = ITextFont_GetOutline(font, &value);
    CHARFORMAT_SET_B_FIELD(OUTLINE, value);

    value = tomUndefined;
    hr = ITextFont_GetProtected(font, &value);
    CHARFORMAT_SET_B_FIELD(PROTECTED, value);

    value = tomUndefined;
    hr = ITextFont_GetShadow(font, &value);
    CHARFORMAT_SET_B_FIELD(SHADOW, value);

    value = tomUndefined;
    hr = ITextFont_GetSmallCaps(font, &value);
    CHARFORMAT_SET_B_FIELD(SMALLCAPS, value);

    value = tomUndefined;
    hr = ITextFont_GetStrikeThrough(font, &value);
    CHARFORMAT_SET_B_FIELD(STRIKEOUT, value);

    value = tomUndefined;
    hr = ITextFont_GetSubscript(font, &value);
    CHARFORMAT_SET_B_FIELD(SUBSCRIPT, value);

    value = tomUndefined;
    hr = ITextFont_GetSuperscript(font, &value);
    CHARFORMAT_SET_B_FIELD(SUPERSCRIPT, value);

    value = tomUndefined;
    hr = ITextFont_GetUnderline(font, &value);
    CHARFORMAT_SET_B_FIELD(UNDERLINE, value);

#undef CHARFORMAT_SET_B_FIELD

    value = tomUndefined;
    hr = ITextFont_GetAnimation(font, &value);
    if (hr == S_OK && value != tomUndefined) {
        fmt.dwMask |= CFM_ANIMATION;
        fmt.bAnimation = value;
    }

    value = tomUndefined;
    hr = ITextFont_GetBackColor(font, &value);
    if (hr == S_OK && value != tomUndefined) {
        fmt.dwMask |= CFM_BACKCOLOR;
        if (value == tomAutoColor)
            fmt.dwEffects |= CFE_AUTOBACKCOLOR;
        else
            fmt.crBackColor = value;
    }

    value = tomUndefined;
    hr = ITextFont_GetForeColor(font, &value);
    if (hr == S_OK && value != tomUndefined) {
        fmt.dwMask |= CFM_COLOR;
        if (value == tomAutoColor)
            fmt.dwEffects |= CFE_AUTOCOLOR;
        else
            fmt.crTextColor = value;
    }

    value = tomUndefined;
    hr = ITextFont_GetKerning(font, &f);
    if (hr == S_OK && f != tomUndefined) {
        fmt.dwMask |= CFM_KERNING;
        fmt.wKerning = points_to_twips(f);
    }

    value = tomUndefined;
    hr = ITextFont_GetLanguageID(font, &value);
    if (hr == S_OK && value != tomUndefined) {
        fmt.dwMask |= CFM_LCID;
        fmt.lcid = value;
    }

    if (ITextFont_GetName(font, &str) == S_OK) {
        fmt.dwMask |= CFM_FACE;
        lstrcpynW(fmt.szFaceName, str, ARRAY_SIZE(fmt.szFaceName));
        SysFreeString(str);
    }

    hr = ITextFont_GetPosition(font, &f);
    if (hr == S_OK && f != tomUndefined) {
        fmt.dwMask |= CFM_OFFSET;
        fmt.yOffset = points_to_twips(f);
    }

    hr = ITextFont_GetSize(font, &f);
    if (hr == S_OK && f != tomUndefined) {
        fmt.dwMask |= CFM_SIZE;
        fmt.yHeight = points_to_twips(f);
    }

    hr = ITextFont_GetSpacing(font, &f);
    if (hr == S_OK && f != tomUndefined) {
        fmt.dwMask |= CFM_SPACING;
        fmt.sSpacing = f;
    }

    hr = ITextFont_GetWeight(font, &value);
    if (hr == S_OK && value != tomUndefined) {
        fmt.dwMask |= CFM_WEIGHT;
        fmt.wWeight = value;
    }

    if (fmt.dwMask) {
        const IRichEditOleImpl *reole = get_range_reole(range);
        ME_Cursor from, to;
        LONG start, end;

        ITextRange_GetStart(range, &start);
        ITextRange_GetEnd(range, &end);

        ME_CursorFromCharOfs(reole->editor, start, &from);
        ME_CursorFromCharOfs(reole->editor, end, &to);
        ME_SetCharFormat(reole->editor, &from, &to, &fmt);
    }
}