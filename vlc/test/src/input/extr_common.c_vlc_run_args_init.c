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
struct vlc_run_args {int verbose; void* test_demux_controls; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  getenv (char*) ; 
 void* getenv_atoi (char*) ; 
 int /*<<< orphan*/  memset (struct vlc_run_args*,int /*<<< orphan*/ ,int) ; 

void vlc_run_args_init(struct vlc_run_args *args)
{
    memset(args, 0, sizeof(struct vlc_run_args));
    args->verbose = getenv_atoi("V");
    if (args->verbose >= 10)
        args->verbose = 9;

    args->name = getenv("VLC_TARGET");
    args->test_demux_controls = getenv_atoi("VLC_DEMUX_CONTROLS");
}