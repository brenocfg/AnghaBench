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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 size_t wcstombs (char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static size_t wctombs(char *dest, wchar_t x)
{
    wchar_t wstr[] = { x, 0 };
    size_t size = wcstombs(NULL, wstr, 0);
    if (size != (size_t) - 1)
	size = wcstombs(dest, wstr, size + 1);
    return size;
}