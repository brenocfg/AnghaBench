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
typedef  scalar_t__* LPWSTR ;

/* Variables and functions */
 scalar_t__* strchrW (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPWSTR folder_split_path(LPWSTR p, WCHAR ch)
{
    if (!p)
        return p;
    p = strchrW(p, ch);
    if (!p)
        return p;
    *p = 0;
    return p+1;
}