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
 int /*<<< orphan*/  libvlc_audio_filter_list_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_new (int,char const**) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_video_filter_list_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/  test_moduledescriptionlist (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_audiovideofilterlists (const char ** argv, int argc)
{
    libvlc_instance_t *vlc;

    test_log ("Testing libvlc_(audio|video)_filter_list_get()\n");

    vlc = libvlc_new (argc, argv);
    assert (vlc != NULL);

    test_moduledescriptionlist (libvlc_audio_filter_list_get (vlc));
    test_moduledescriptionlist (libvlc_video_filter_list_get (vlc));

    libvlc_release (vlc);
}