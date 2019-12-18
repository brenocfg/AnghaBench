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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * libvlc_new (int,char const**) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_retain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_log (char*) ; 

__attribute__((used)) static void test_core (const char ** argv, int argc)
{
    libvlc_instance_t *vlc;

    test_log ("Testing core\n");

    vlc = libvlc_new (argc, argv);
    assert (vlc != NULL);

    libvlc_retain (vlc);
    libvlc_release (vlc);
    libvlc_release (vlc);
}