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
 int /*<<< orphan*/  args ; 
 scalar_t__ libvlc_create (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc ; 
 int /*<<< orphan*/  vlc_run_args_init (int /*<<< orphan*/ *) ; 

int LLVMFuzzerInitialize(int *argc, char ***argv)
{
    (void) argc; (void) argv;

    vlc_run_args_init(&args);
    vlc = libvlc_create(&args);

    return vlc ? 0 : -1;
}