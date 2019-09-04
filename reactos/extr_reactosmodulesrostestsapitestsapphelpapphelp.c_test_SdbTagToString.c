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
typedef  int WORD ;
typedef  char WCHAR ;
typedef  int TAG ;
typedef  char const* LPCWSTR ;

/* Variables and functions */
#define  TAG_TYPE_DWORD 130 
#define  TAG_TYPE_MASK 129 
#define  TAG_TYPE_WORD 128 
 scalar_t__ lstrcmpW (char const*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pSdbTagToString (int const) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char const*) ; 

__attribute__((used)) static void test_SdbTagToString(void)
{
    static const TAG invalid_values[] = {
        1, TAG_TYPE_WORD, TAG_TYPE_MASK,
        TAG_TYPE_DWORD | 0xFF,
        TAG_TYPE_DWORD | (0x800 + 0xEE),
        0x900, 0xFFFF, 0xDEAD, 0xBEEF
    };
    static const WCHAR invalid[] = {'I','n','v','a','l','i','d','T','a','g',0};
    LPCWSTR ret;
    WORD i;

    for (i = 0; i < 9; ++i)
    {
        ret = pSdbTagToString(invalid_values[i]);
        ok(lstrcmpW(ret, invalid) == 0, "unexpected string %s, should be %s\n",
           wine_dbgstr_w(ret), wine_dbgstr_w(invalid));
    }
}