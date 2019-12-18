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

/* Variables and functions */
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ) ; 
 char* default_cmd_line1 ; 
 char* default_cmd_line2 ; 
 char* default_cmd_line3 ; 
 char* default_cmd_line4 ; 
 char* default_cmd_line5 ; 
 char* default_cmd_line6 ; 
 char* default_cmd_line7 ; 
 char* default_cmd_line8 ; 
 char* default_cmd_line9 ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void show_menu(void)
{
    _tprintf(_T("\nchoose test :\n"));
    _tprintf(_T("  0 = Exit\n"));
         printf("  1 = %s\n", default_cmd_line1);
         printf("  2 = %s\n", default_cmd_line2);
         printf("  3 = %s\n", default_cmd_line3);
         printf("  4 = %s\n", default_cmd_line4);
         printf("  5 = %s\n", default_cmd_line5);
         printf("  6 = %s\n", default_cmd_line6);
         printf("  7 = %s\n", default_cmd_line7);
         printf("  8 = %s\n", default_cmd_line8);
         printf("  9 = %s\n", default_cmd_line9);
/*
    _tprintf(_T("  1 = %s\n"), default_cmd_line1);
    _tprintf(_T("  2 = %s\n"), default_cmd_line2);
    _tprintf(_T("  3 = %s\n"), default_cmd_line3);
    _tprintf(_T("  4 = %s\n"), default_cmd_line4);
    _tprintf(_T("  5 = %s\n"), default_cmd_line5);
    _tprintf(_T("  6 = %s\n"), default_cmd_line6);
    _tprintf(_T("  7 = %s\n"), default_cmd_line7);
    _tprintf(_T("  8 = %s\n"), default_cmd_line8);
    _tprintf(_T("  9 = %s\n"), default_cmd_line9);
 */
//        _tprintf(_T("  A = HKEY_CLASSES_ROOT\n"));
//        _tprintf(_T("  B = HKEY_CURRENT_USER\n"));
//        _tprintf(_T("  C = HKEY_LOCAL_MACHINE\n"));
//        _tprintf(_T("  D = HKEY_USERS\n"));
//        _tprintf(_T("  E = HKEY_CURRENT_CONFIG\n"));
//        _tprintf(_T("  F = REGISTRY ROOT\n"));
}