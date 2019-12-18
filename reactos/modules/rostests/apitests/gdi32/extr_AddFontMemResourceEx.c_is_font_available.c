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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  CreateFontA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  DEFAULT_CHARSET ; 
 int /*<<< orphan*/  DEFAULT_PITCH ; 
 int /*<<< orphan*/  DEFAULT_QUALITY ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  FW_DONTCARE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetTextFaceA (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  OUT_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  _strcmpi (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static BOOL is_font_available(HDC hdc, const char* fontName)
{
    char name[64];
    BOOL ret;

    HFONT font = CreateFontA(0, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, fontName);
    HGDIOBJ old = SelectObject(hdc, font);


    SetLastError(0xdeadbeef);

    ret = GetTextFaceA(hdc, sizeof(name), name);
    ok(ret, "GetTextFaceA error %lu for %s\n", GetLastError(), fontName);
    SelectObject(hdc, old);
    DeleteObject(font);

    if (ret)
    {
        return !_strcmpi(name, fontName);
    }
    return FALSE;
}