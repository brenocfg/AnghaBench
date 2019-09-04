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
typedef  int /*<<< orphan*/  query ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;

/* Variables and functions */
 int CLOSECHANNEL ; 
 int DOWNLOADFACE ; 
 int DOWNLOADHEADER ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int Escape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ExtEscape (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int GETFACENAME ; 
 int OPENCHANNEL ; 
 int POSTSCRIPT_PASSTHROUGH ; 
 int /*<<< orphan*/  QUERYESCSUPPORT ; 
 int /*<<< orphan*/  create_printer_dc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_postscript_printer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  print_something (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void test_pscript_printer_dc(void)
{
    HDC hdc;
    char buf[256];
    DWORD query, ret;

    hdc = create_printer_dc(100, FALSE);

    if (!hdc) return;

    if (!is_postscript_printer(hdc))
    {
        skip("Default printer is not a PostScript device\n");
        DeleteDC( hdc );
        return;
    }

    query = GETFACENAME;
    ret = Escape(hdc, QUERYESCSUPPORT, sizeof(query), (LPCSTR)&query, NULL);
    ok(!ret, "GETFACENAME is supported\n");

    query = DOWNLOADFACE;
    ret = Escape(hdc, QUERYESCSUPPORT, sizeof(query), (LPCSTR)&query, NULL);
    ok(ret == 1, "DOWNLOADFACE is not supported\n");

    query = OPENCHANNEL;
    ret = Escape(hdc, QUERYESCSUPPORT, sizeof(query), (LPCSTR)&query, NULL);
    ok(ret == 1, "OPENCHANNEL is not supported\n");

    query = DOWNLOADHEADER;
    ret = Escape(hdc, QUERYESCSUPPORT, sizeof(query), (LPCSTR)&query, NULL);
    ok(ret == 1, "DOWNLOADHEADER is not supported\n");

    query = CLOSECHANNEL;
    ret = Escape(hdc, QUERYESCSUPPORT, sizeof(query), (LPCSTR)&query, NULL);
    ok(ret == 1, "CLOSECHANNEL is not supported\n");

    query = POSTSCRIPT_PASSTHROUGH;
    ret = Escape(hdc, QUERYESCSUPPORT, sizeof(query), (LPCSTR)&query, NULL);
    ok(ret == 1, "POSTSCRIPT_PASSTHROUGH is not supported\n");

    ret = ExtEscape(hdc, GETFACENAME, 0, NULL, sizeof(buf), buf);
    ok(ret == 1, "GETFACENAME failed\n");
    trace("face name: %s\n", buf);

    print_something(hdc);

    DeleteDC(hdc);
}