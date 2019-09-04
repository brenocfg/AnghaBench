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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_10__ {int dwMask; scalar_t__ bCharSet; int /*<<< orphan*/ * szFaceName; } ;
struct TYPE_9__ {scalar_t__ bCharSet; int /*<<< orphan*/ * szFaceName; } ;
struct TYPE_8__ {int nFontTblLen; TYPE_3__* fonttbl; } ;
struct TYPE_7__ {TYPE_4__ fmt; } ;
typedef  TYPE_1__ ME_Style ;
typedef  TYPE_2__ ME_OutStream ;
typedef  TYPE_3__ ME_FontTableItem ;
typedef  TYPE_4__ CHARFORMAT2W ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int CFM_CHARSET ; 
 int CFM_FACE ; 
 scalar_t__ DEFAULT_CHARSET ; 
 int STREAMOUT_FONTTBL_SIZE ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_font_to_fonttbl( ME_OutStream *stream, ME_Style *style )
{
    ME_FontTableItem *table = stream->fonttbl;
    CHARFORMAT2W *fmt = &style->fmt;
    WCHAR *face = fmt->szFaceName;
    BYTE charset = (fmt->dwMask & CFM_CHARSET) ? fmt->bCharSet : DEFAULT_CHARSET;
    int i;

    if (fmt->dwMask & CFM_FACE)
    {
        for (i = 0; i < stream->nFontTblLen; i++)
            if (table[i].bCharSet == charset
                && (table[i].szFaceName == face || !lstrcmpW(table[i].szFaceName, face)))
                break;

        if (i == stream->nFontTblLen && i < STREAMOUT_FONTTBL_SIZE)
        {
            table[i].bCharSet = charset;
            table[i].szFaceName = face;
            stream->nFontTblLen++;
        }
    }
}