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

/* Variables and functions */
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _TEOF ; 
 int /*<<< orphan*/  _THEX_FORMAT ; 
 int /*<<< orphan*/  _gettc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static int test_console_getchar(void)
{
    int result = 0;
    TCHAR ch;

    _tprintf(_T("Enter lines for dumping or <ctrl-z><nl> to finish:\n"));

    //while ((ch = _gettchar()) != _TEOF) {
    while ((ch = _gettc(stdin)) != _TEOF) {
        _tprintf(_THEX_FORMAT, ch);
        //printf("0x%04x ", ch);
    }
    return result;
}