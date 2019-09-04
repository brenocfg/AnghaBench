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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int lstrlenW (int /*<<< orphan*/  const*) ; 
 int memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int strcmp_w(const WCHAR *str1, const WCHAR *str2)
{
    DWORD len1 = lstrlenW(str1);
    DWORD len2 = lstrlenW(str2);

    if(len1!=len2) return 1;
    return memcmp(str1, str2, len1*sizeof(WCHAR));
}