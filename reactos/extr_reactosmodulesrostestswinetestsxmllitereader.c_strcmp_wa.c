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

/* Variables and functions */
 int /*<<< orphan*/ * a2w (char const*) ; 
 int /*<<< orphan*/  free_str (int /*<<< orphan*/ *) ; 
 int lstrcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int strcmp_wa(const WCHAR *str1, const char *stra)
{
    WCHAR *str2 = a2w(stra);
    int r = lstrcmpW(str1, str2);
    free_str(str2);
    return r;
}