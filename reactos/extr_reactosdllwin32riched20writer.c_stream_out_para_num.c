#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int wNumbering; int wNumberingStyle; int /*<<< orphan*/  wNumberingStart; int /*<<< orphan*/  wNumberingTab; } ;
struct TYPE_9__ {TYPE_2__* text; TYPE_1__* style; } ;
struct TYPE_11__ {TYPE_4__ fmt; TYPE_3__ para_num; } ;
struct TYPE_8__ {int /*<<< orphan*/  nLen; int /*<<< orphan*/  szData; } ;
struct TYPE_7__ {int /*<<< orphan*/  fmt; } ;
typedef  TYPE_5__ ME_Paragraph ;
typedef  int /*<<< orphan*/  ME_OutStream ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ME_StreamOutPrint (int /*<<< orphan*/ *,char const*,...) ; 
 int /*<<< orphan*/  ME_StreamOutRTFText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PFNS_PAREN 135 
#define  PFNS_PARENS 134 
#define  PFNS_PERIOD 133 
#define  PFN_ARABIC 132 
 int PFN_BULLET ; 
#define  PFN_LCLETTER 131 
#define  PFN_LCROMAN 130 
#define  PFN_UCLETTER 129 
#define  PFN_UCROMAN 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  find_font_in_fonttbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static BOOL stream_out_para_num( ME_OutStream *stream, ME_Paragraph *para, BOOL pn_dest )
{
    static const char fmt_label[] = "{\\*\\pn\\pnlvlbody\\pnf%u\\pnindent%d\\pnstart%d%s%s}";
    static const char fmt_bullet[] = "{\\*\\pn\\pnlvlblt\\pnf%u\\pnindent%d{\\pntxtb\\'b7}}";
    static const char dec[] = "\\pndec";
    static const char lcltr[] = "\\pnlcltr";
    static const char ucltr[] = "\\pnucltr";
    static const char lcrm[] = "\\pnlcrm";
    static const char ucrm[] = "\\pnucrm";
    static const char period[] = "{\\pntxta.}";
    static const char paren[] = "{\\pntxta)}";
    static const char parens[] = "{\\pntxtb(}{\\pntxta)}";
    const char *type, *style = "";
    unsigned int idx;

    find_font_in_fonttbl( stream, &para->para_num.style->fmt, &idx );

    if (!ME_StreamOutPrint( stream, "{\\pntext\\f%u ", idx )) return FALSE;
    if (!ME_StreamOutRTFText( stream, para->para_num.text->szData, para->para_num.text->nLen ))
        return FALSE;
    if (!ME_StreamOutPrint( stream, "\\tab}" )) return FALSE;

    if (!pn_dest) return TRUE;

    if (para->fmt.wNumbering == PFN_BULLET)
    {
        if (!ME_StreamOutPrint( stream, fmt_bullet, idx, para->fmt.wNumberingTab ))
            return FALSE;
    }
    else
    {
        switch (para->fmt.wNumbering)
        {
        case PFN_ARABIC:
        default:
            type = dec;
            break;
        case PFN_LCLETTER:
            type = lcltr;
            break;
        case PFN_UCLETTER:
            type = ucltr;
            break;
        case PFN_LCROMAN:
            type = lcrm;
            break;
        case PFN_UCROMAN:
            type = ucrm;
            break;
        }
        switch (para->fmt.wNumberingStyle & 0xf00)
        {
        case PFNS_PERIOD:
            style = period;
            break;
        case PFNS_PAREN:
            style = paren;
            break;
        case PFNS_PARENS:
            style = parens;
            break;
        }

        if (!ME_StreamOutPrint( stream, fmt_label, idx, para->fmt.wNumberingTab,
                                para->fmt.wNumberingStart, type, style ))
            return FALSE;
    }
    return TRUE;
}