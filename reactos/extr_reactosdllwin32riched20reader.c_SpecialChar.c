#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int cbSize; } ;
struct TYPE_14__ {int rtfMinor; int rtfParam; int unicodeLength; TYPE_10__* editor; TYPE_2__ fmt; int /*<<< orphan*/  rtfMajor; int /*<<< orphan*/  rtfClass; } ;
struct TYPE_13__ {int /*<<< orphan*/  bEmulateVersion10; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ME_InsertEndRowFromCursor (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_SetSelectionParaFormat (TYPE_10__*,TYPE_2__*) ; 
 int /*<<< orphan*/  RTFFlushOutputBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  RTFGetToken (TYPE_1__*) ; 
 int /*<<< orphan*/  RTFPutUnicodeChar (TYPE_1__*,int) ; 
 int /*<<< orphan*/  RTFRouteToken (TYPE_1__*) ; 
 int /*<<< orphan*/  RTFSkipGroup (TYPE_1__*) ; 
 int /*<<< orphan*/  RTFUngetToken (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
#define  rtfBullet 149 
 int /*<<< orphan*/  rtfDestination ; 
#define  rtfEmDash 148 
#define  rtfEmSpace 147 
#define  rtfEnDash 146 
#define  rtfEnSpace 145 
#define  rtfLDblQuote 144 
#define  rtfLQuote 143 
#define  rtfLTRMark 142 
#define  rtfLine 141 
#define  rtfNoBrkHyphen 140 
#define  rtfNoBrkSpace 139 
#define  rtfNoWidthJoiner 138 
#define  rtfNoWidthNonJoiner 137 
#define  rtfOptDest 136 
#define  rtfPage 135 
#define  rtfPar 134 
#define  rtfRDblQuote 133 
#define  rtfRQuote 132 
#define  rtfRTLMark 131 
#define  rtfSect 130 
#define  rtfTab 129 
 int /*<<< orphan*/  rtfText ; 
#define  rtfUnicode 128 

__attribute__((used)) static void SpecialChar (RTF_Info *info)
{
	switch (info->rtfMinor)
	{
	case rtfOptDest:
		/* the next token determines destination, if it's unknown, skip the group */
		/* this way we filter out the garbage coming from unknown destinations */ 
		RTFGetToken(info); 
		if (info->rtfClass != rtfDestination)
			RTFSkipGroup(info);
		else
			RTFRouteToken(info); /* "\*" is ignored with known destinations */
		break;
	case rtfUnicode:
	{
                int i;

                RTFPutUnicodeChar(info, info->rtfParam);

                /* After \u we must skip number of character tokens set by \ucN */
                for (i = 0; i < info->unicodeLength; i++)
                {
			RTFGetToken(info);
                        if (info->rtfClass != rtfText)
		        {
                                ERR("The token behind \\u is not text, but (%d,%d,%d)\n",
				info->rtfClass, info->rtfMajor, info->rtfMinor);
                                RTFUngetToken(info);
                                break;
                        }
		}
		break;
	}
	case rtfLine:
            RTFFlushOutputBuffer(info);
            ME_InsertEndRowFromCursor(info->editor, 0);
            break;
	case rtfPage:
	case rtfSect:
	case rtfPar:
                RTFFlushOutputBuffer(info);
                ME_SetSelectionParaFormat(info->editor, &info->fmt);
                memset(&info->fmt, 0, sizeof(info->fmt));
                info->fmt.cbSize = sizeof(info->fmt);
		RTFPutUnicodeChar (info, '\r');
		if (info->editor->bEmulateVersion10) RTFPutUnicodeChar (info, '\n');
		break;
	case rtfNoBrkSpace:
		RTFPutUnicodeChar (info, 0x00A0);
		break;
	case rtfTab:
		RTFPutUnicodeChar (info, '\t');
		break;
	case rtfNoBrkHyphen:
		RTFPutUnicodeChar (info, 0x2011);
		break;
	case rtfBullet:
		RTFPutUnicodeChar (info, 0x2022);
		break;
	case rtfEmDash:
		RTFPutUnicodeChar (info, 0x2014);
		break;
	case rtfEnDash:
		RTFPutUnicodeChar (info, 0x2013);
		break;
        case rtfEmSpace:
                RTFPutUnicodeChar (info, ' ');
                break;
        case rtfEnSpace:
                RTFPutUnicodeChar (info, ' ');
                break;
	case rtfLQuote:
		RTFPutUnicodeChar (info, 0x2018);
		break;
	case rtfRQuote:
		RTFPutUnicodeChar (info, 0x2019);
		break;
	case rtfLDblQuote:
		RTFPutUnicodeChar (info, 0x201C);
		break;
	case rtfRDblQuote:
		RTFPutUnicodeChar (info, 0x201D);
		break;
        case rtfLTRMark:
                RTFPutUnicodeChar (info, 0x200E);
                break;
        case rtfRTLMark:
                RTFPutUnicodeChar (info, 0x200F);
                break;
        case rtfNoWidthJoiner:
                RTFPutUnicodeChar (info, 0x200D);
                break;
        case rtfNoWidthNonJoiner:
                RTFPutUnicodeChar (info, 0x200C);
                break;
	}
}