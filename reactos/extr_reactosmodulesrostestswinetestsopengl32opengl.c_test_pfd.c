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
typedef  int /*<<< orphan*/  PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int ChoosePixelFormat (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CreateWindowA (char*,char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DescribePixelFormat (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_pfd(const PIXELFORMATDESCRIPTOR *pfd, PIXELFORMATDESCRIPTOR *fmt)
{
    int pf;
    HDC hdc;
    HWND hwnd;

    hwnd = CreateWindowA("static", "Title", WS_OVERLAPPEDWINDOW, 10, 10, 200, 200, NULL, NULL,
            NULL, NULL);
    if (!hwnd)
        return 0;

    hdc = GetDC( hwnd );
    pf = ChoosePixelFormat( hdc, pfd );
    if (pf && fmt)
    {
        memset(fmt, 0, sizeof(*fmt));
        ok(DescribePixelFormat( hdc, pf, sizeof(*fmt), fmt ),
           "DescribePixelFormat failed with error: %u\n", GetLastError());
    }
    ReleaseDC( hwnd, hdc );
    DestroyWindow( hwnd );

    return pf;
}