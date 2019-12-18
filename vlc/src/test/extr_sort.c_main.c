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

/* Variables and functions */
 int /*<<< orphan*/  test_equal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_smaller (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_filenamecmp ; 

int main (void)
{
    test_smaller("", "a", vlc_filenamecmp);
    test_smaller("a", "b", vlc_filenamecmp);
    test_smaller("foo1.ogg", "foo2.ogg", vlc_filenamecmp);
    test_smaller("foo2.ogg", "foo10.ogg", vlc_filenamecmp);
    test_smaller("foo1.ogg", "foo10.ogg", vlc_filenamecmp);
    test_smaller("foo01.ogg", "foo1.ogg", vlc_filenamecmp);
    test_equal("", vlc_filenamecmp);
    test_equal("a", vlc_filenamecmp);
    test_equal("123", vlc_filenamecmp);
    return 0;
}