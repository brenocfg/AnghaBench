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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HINSTANCE ;
typedef  int /*<<< orphan*/  HICON ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_HINSTANCE ; 
 scalar_t__ GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDI_STARFIELD ; 
 int /*<<< orphan*/  IDS_AUTHOR ; 
 int /*<<< orphan*/  IDS_DESCRIPTION ; 
 int /*<<< orphan*/  IDS_LICENSE ; 
 int /*<<< orphan*/  LoadIcon (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadString (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShellAbout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * _T (char*) ; 
 int /*<<< orphan*/  _tcscat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL OnCommandAbout(HWND hWnd)
{
    HINSTANCE hInstance;
    HICON     hIcon;
    TCHAR     szAppName[256];
    TCHAR     szAuthor[256];
    TCHAR     szLicense[1024];

    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);

    hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STARFIELD));

    LoadString(hInstance, IDS_DESCRIPTION, szAppName, SIZEOF(szAppName));
    LoadString(hInstance, IDS_AUTHOR,      szAuthor,  SIZEOF(szAuthor));
    LoadString(hInstance, IDS_LICENSE,     szLicense, SIZEOF(szLicense));

    _tcscat(szAppName, _T("#"));
    _tcscat(szAppName, szAuthor);

    ShellAbout(hWnd, szAppName, szLicense, hIcon);

    return TRUE;
}