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
 int NORM_IGNORECASE ; 
 int NORM_IGNORENONSPACE ; 
 int compare_case_weights (int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int) ; 
 int compare_diacritic_weights (int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int) ; 
 int compare_unicode_weights (int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int) ; 

int wine_compare_string(int flags, const WCHAR *str1, int len1,
                        const WCHAR *str2, int len2)
{
    int ret;

    ret = compare_unicode_weights(flags, str1, len1, str2, len2);
    if (!ret)
    {
        if (!(flags & NORM_IGNORENONSPACE))
            ret = compare_diacritic_weights(flags, str1, len1, str2, len2);
        if (!ret && !(flags & NORM_IGNORECASE))
            ret = compare_case_weights(flags, str1, len1, str2, len2);
    }
    return ret;
}