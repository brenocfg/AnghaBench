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
typedef  int /*<<< orphan*/  tm ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_6__ {scalar_t__ FontName; } ;
typedef  TYPE_1__ fnt_res ;
struct TYPE_8__ {char* ResourceName; TYPE_1__* res; } ;
struct TYPE_7__ {int /*<<< orphan*/  tmCharSet; int /*<<< orphan*/  tmPitchAndFamily; int /*<<< orphan*/  tmStruckOut; int /*<<< orphan*/  tmUnderlined; int /*<<< orphan*/  tmItalic; int /*<<< orphan*/  tmBreakChar; int /*<<< orphan*/  tmDefaultChar; int /*<<< orphan*/  tmLastChar; int /*<<< orphan*/  tmFirstChar; int /*<<< orphan*/  tmDigitizedAspectY; int /*<<< orphan*/  tmDigitizedAspectX; int /*<<< orphan*/  tmOverhang; int /*<<< orphan*/  tmWeight; int /*<<< orphan*/  tmMaxCharWidth; int /*<<< orphan*/  tmAveCharWidth; int /*<<< orphan*/  tmExternalLeading; int /*<<< orphan*/  tmInternalLeading; int /*<<< orphan*/  tmDescent; int /*<<< orphan*/  tmAscent; int /*<<< orphan*/  tmHeight; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ TEXTMETRICA ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  CreateFontA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DEFAULT_CHARSET ; 
 int /*<<< orphan*/  DEFAULT_PITCH ; 
 int /*<<< orphan*/  DEFAULT_QUALITY ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FW_DONTCARE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetTextFaceA (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ GetTextMetricsA (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  OUT_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  ok_hex2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_int2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 
 TYPE_3__* test_data ; 

__attribute__((used)) static void test_font_caps(HDC hdc, int test_index)
{
    HGDIOBJ old;
    TEXTMETRICA tm = { 0 };
    char name[64];
    BOOL ret;
    HFONT font;
    int n;
    const char* test_name = test_data[test_index].ResourceName;

    for (n = 0; test_data[test_index].res[n].FontName; ++n)
    {
        fnt_res* res = test_data[test_index].res + n;
        font = CreateFontA(0, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                     OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, res->FontName);

        if (font)
        {
            old = SelectObject(hdc, font);

            memset(&tm, 0xaa, sizeof(tm));
            ret = GetTextMetricsA(hdc, &tm);
            ok(ret, "GetTextMetricsA() for %s/%s\n", test_name, res->FontName);

            SetLastError(0xdeadbeef);
            ret = GetTextFaceA(hdc, sizeof(name), name);
            ok(ret, "GetTextFaceA error %lu for %s/%s\n", GetLastError(), test_name, res->FontName);
            if (ret)
            {
                ok(!strcmp(name, res->FontName), "FontName was %s, expected %s for %s/%s", name, res->FontName, test_name, res->FontName);
            }

            ok_int2(tm.tmHeight);
            ok_int2(tm.tmAscent);
            ok_int2(tm.tmDescent);
            ok_int2(tm.tmInternalLeading);
            ok_int2(tm.tmExternalLeading);
            ok_int2(tm.tmAveCharWidth);
            ok_int2(tm.tmMaxCharWidth);
            ok_int2(tm.tmWeight);
            ok_int2(tm.tmOverhang);
            ok_int2(tm.tmDigitizedAspectX);
            ok_int2(tm.tmDigitizedAspectY);
            ok_int2(tm.tmFirstChar);
            ok_int2(tm.tmLastChar);
            ok_int2(tm.tmDefaultChar);
            ok_int2(tm.tmBreakChar);
            ok_int2(tm.tmItalic);
            ok_int2(tm.tmUnderlined);
            ok_int2(tm.tmStruckOut);
            ok_hex2(tm.tmPitchAndFamily);
            ok_int2(tm.tmCharSet);

            SelectObject(hdc, old);
            DeleteObject(font);
        }
    }
}