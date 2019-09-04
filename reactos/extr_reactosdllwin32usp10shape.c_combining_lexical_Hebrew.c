#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int WCHAR ;

/* Variables and functions */

__attribute__((used)) static int combining_lexical_Hebrew(WCHAR c)
{
    enum {Hebr_Norm=0, Hebr_DIAC, Hebr_CANT1, Hebr_CANT2, Hebr_CANT3, Hebr_CANT4, Hebr_CANT5, Hebr_CANT6, Hebr_CANT7, Hebr_CANT8, Hebr_CANT9, Hebr_CANT10, Hebr_DAGESH, Hebr_DOTABV, Hebr_HOLAM, Hebr_METEG, Hebr_PATAH, Hebr_QAMATS, Hebr_RAFE, Hebr_SHINSIN};

   switch(c)
    {
        case 0x05B0:
        case 0x05B1:
        case 0x05B2:
        case 0x05B3:
        case 0x05B4:
        case 0x05B5:
        case 0x05B6:
        case 0x05BB: return Hebr_DIAC;
        case 0x0599:
        case 0x05A1:
        case 0x05A9:
        case 0x05AE: return Hebr_CANT1;
        case 0x0597:
        case 0x05A8:
        case 0x05AC: return Hebr_CANT2;
        case 0x0592:
        case 0x0593:
        case 0x0594:
        case 0x0595:
        case 0x05A7:
        case 0x05AB: return Hebr_CANT3;
        case 0x0598:
        case 0x059C:
        case 0x059E:
        case 0x059F: return Hebr_CANT4;
        case 0x059D:
        case 0x05A0: return Hebr_CANT5;
        case 0x059B:
        case 0x05A5: return Hebr_CANT6;
        case 0x0591:
        case 0x05A3:
        case 0x05A6: return Hebr_CANT7;
        case 0x0596:
        case 0x05A4:
        case 0x05AA: return Hebr_CANT8;
        case 0x059A:
        case 0x05AD: return Hebr_CANT9;
        case 0x05AF: return Hebr_CANT10;
        case 0x05BC: return Hebr_DAGESH;
        case 0x05C4: return Hebr_DOTABV;
        case 0x05B9: return Hebr_HOLAM;
        case 0x05BD: return Hebr_METEG;
        case 0x05B7: return Hebr_PATAH;
        case 0x05B8: return Hebr_QAMATS;
        case 0x05BF: return Hebr_RAFE;
        case 0x05C1:
        case 0x05C2: return Hebr_SHINSIN;
        default: return Hebr_Norm;
    }
}