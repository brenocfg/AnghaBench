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
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_new (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_cancel_thumbnail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_init () ; 
 int /*<<< orphan*/  test_thumbnails (int /*<<< orphan*/ *) ; 

int main()
{
    test_init();

    static const char * argv[] = {
        "-v",
        "--ignore-config",
    };
    libvlc_instance_t *vlc = libvlc_new(ARRAY_SIZE(argv), argv);
    assert(vlc);

    test_thumbnails( vlc );
    test_cancel_thumbnail( vlc );

    libvlc_release( vlc );
}