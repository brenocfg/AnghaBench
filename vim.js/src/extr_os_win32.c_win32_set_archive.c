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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int FILE_ATTRIBUTE_ARCHIVE ; 
 int win32_getattrs (int /*<<< orphan*/ *) ; 
 int win32_setattrs (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
    int
win32_set_archive(char_u *name)
{
    int attrs = win32_getattrs(name);
    if (attrs == -1)
	return -1;

    attrs |= FILE_ATTRIBUTE_ARCHIVE;
    return win32_setattrs(name, attrs);
}