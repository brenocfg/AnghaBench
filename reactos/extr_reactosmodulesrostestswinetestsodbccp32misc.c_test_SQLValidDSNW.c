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
typedef  int BOOL ;

/* Variables and functions */
 int SQLValidDSNW (char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_SQLValidDSNW(void)
{
    static const WCHAR invalid[] = {'[',']','{','}','(',')',',',';','?','*','=','!','@','\\',0};
    static const WCHAR value[] = { 'w','i','n','e','1','0',0};
    static const WCHAR too_large[] = { 'W','i','n','e','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5',
                                   '6','7','8','9','0','1','2','3','4','5','6','7','8','9','0', 0};
    static const WCHAR with_space[] = { 'W','i','n','e',' ','V','i','n','e','g','a','r', 0};
    static const WCHAR max_dsn[] = { '1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0',
                                   '1','2','3','4','5','6','7','8','9','0','1','2', 0};
    WCHAR str[10];
    int i;
    BOOL ret;

    lstrcpyW(str, value);
    for(i = 0; i < lstrlenW(invalid); i++)
    {
        str[4] = invalid[i];
        ret = SQLValidDSNW(str);
        ok(!ret, "got %d\n", ret);
    }

    ret = SQLValidDSNW(too_large);
    ok(!ret, "got %d\n", ret);

    ret = SQLValidDSNW(with_space);
    ok(ret, "got %d\n", ret);

    ret = SQLValidDSNW(max_dsn);
    ok(ret, "got %d\n", ret);
}