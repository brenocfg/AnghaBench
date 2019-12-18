#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_8__ {scalar_t__ lfFaceName; int /*<<< orphan*/  lfPitchAndFamily; int /*<<< orphan*/  lfQuality; int /*<<< orphan*/  lfClipPrecision; int /*<<< orphan*/  lfOutPrecision; int /*<<< orphan*/  lfCharSet; int /*<<< orphan*/  lfStrikeOut; int /*<<< orphan*/  lfUnderline; int /*<<< orphan*/  lfItalic; int /*<<< orphan*/  lfWeight; int /*<<< orphan*/  lfOrientation; int /*<<< orphan*/  lfEscapement; int /*<<< orphan*/  lfWidth; int /*<<< orphan*/  lfHeight; } ;
struct TYPE_7__ {int /*<<< orphan*/  lfFaceName; int /*<<< orphan*/  lfPitchAndFamily; int /*<<< orphan*/  lfQuality; int /*<<< orphan*/  lfClipPrecision; int /*<<< orphan*/  lfOutPrecision; int /*<<< orphan*/  lfCharSet; int /*<<< orphan*/  lfStrikeOut; int /*<<< orphan*/  lfUnderline; int /*<<< orphan*/  lfItalic; int /*<<< orphan*/  lfWeight; int /*<<< orphan*/  lfOrientation; int /*<<< orphan*/  lfEscapement; int /*<<< orphan*/  lfWidth; int /*<<< orphan*/  lfHeight; } ;
struct TYPE_6__ {int rdSize; int /*<<< orphan*/  rdParm; int /*<<< orphan*/  rdFunction; } ;
typedef  int /*<<< orphan*/  PHYSDEV ;
typedef  TYPE_1__ METARECORD ;
typedef  TYPE_2__ LOGFONTW ;
typedef  TYPE_3__ LOGFONT16 ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HFONT ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ LF_FACESIZE ; 
 int /*<<< orphan*/  META_CREATEFONTINDIRECT ; 
 int /*<<< orphan*/  MFDRV_AddHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFDRV_WriteRecord (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static UINT16 MFDRV_CreateFontIndirect(PHYSDEV dev, HFONT hFont, LOGFONTW *logfont)
{
    char buffer[sizeof(METARECORD) - 2 + sizeof(LOGFONT16)];
    METARECORD *mr = (METARECORD *)&buffer;
    LOGFONT16 *font16;
    INT written;

    mr->rdSize = (sizeof(METARECORD) + sizeof(LOGFONT16) - 2) / 2;
    mr->rdFunction = META_CREATEFONTINDIRECT;
    font16 = (LOGFONT16 *)&mr->rdParm;

    font16->lfHeight         = logfont->lfHeight;
    font16->lfWidth          = logfont->lfWidth;
    font16->lfEscapement     = logfont->lfEscapement;
    font16->lfOrientation    = logfont->lfOrientation;
    font16->lfWeight         = logfont->lfWeight;
    font16->lfItalic         = logfont->lfItalic;
    font16->lfUnderline      = logfont->lfUnderline;
    font16->lfStrikeOut      = logfont->lfStrikeOut;
    font16->lfCharSet        = logfont->lfCharSet;
    font16->lfOutPrecision   = logfont->lfOutPrecision;
    font16->lfClipPrecision  = logfont->lfClipPrecision;
    font16->lfQuality        = logfont->lfQuality;
    font16->lfPitchAndFamily = logfont->lfPitchAndFamily;
    written = WideCharToMultiByte( CP_ACP, 0, logfont->lfFaceName, -1, font16->lfFaceName, LF_FACESIZE - 1, NULL, NULL );
    /* Zero pad the facename buffer, so that we don't write uninitialized data to disk */
    memset(font16->lfFaceName + written, 0, LF_FACESIZE - written);

    if (!(MFDRV_WriteRecord( dev, mr, mr->rdSize * 2)))
        return 0;
    return MFDRV_AddHandle( dev, hFont );
}