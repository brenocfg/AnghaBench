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
typedef  scalar_t__ WCHAR ;
typedef  int DWORD ;
typedef  scalar_t__ CompareMethod ;

/* Variables and functions */
 int /*<<< orphan*/  CharLowerW (int /*<<< orphan*/ ) ; 
 scalar_t__ DatabaseCompare ; 
 int /*<<< orphan*/  IntToPtr (scalar_t__ const) ; 
 scalar_t__ PtrToInt (int /*<<< orphan*/ ) ; 
 scalar_t__ TextCompare ; 

__attribute__((used)) static DWORD get_str_hash(const WCHAR *str, CompareMethod method)
{
    DWORD hash = 0;

    while (*str) {
        WCHAR ch;

        if (method == TextCompare || method == DatabaseCompare)
            ch = PtrToInt(CharLowerW(IntToPtr(*str)));
        else
            ch = *str;

        hash += (hash << 4) + ch;
        str++;
    }

    return hash % 1201;
}