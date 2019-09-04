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
typedef  char WCHAR ;
typedef  char* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int,char*) ; 
 char* pStrChrNW (char const*,char,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_StrChrNW(void)
{
    static const WCHAR string[] = {'T','e','s','t','i','n','g',' ','S','t','r','i','n','g',0};
    LPWSTR p;

    if (!pStrChrNW)
    {
        win_skip("StrChrNW not available\n");
        return;
    }

    p = pStrChrNW(string,'t',10);
    ok(*p=='t',"Found wrong 't'\n");
    ok(*(p+1)=='i',"next should be 'i'\n");

    p = pStrChrNW(string,'S',10);
    ok(*p=='S',"Found wrong 'S'\n");

    p = pStrChrNW(string,'r',10);
    ok(p==NULL,"Should not have found 'r'\n");
}