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
struct vlc_run_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int vlc_demux_process_path (struct vlc_run_args*,char const*) ; 
 int /*<<< orphan*/  vlc_run_args_init (struct vlc_run_args*) ; 

int main(int argc, char *argv[])
{
    const char *filename;
    struct vlc_run_args args;
    vlc_run_args_init(&args);

    switch (argc)
    {
        case 2:
            filename = argv[argc - 1];
            break;
        default:
            fprintf(stderr, "Usage: [VLC_TARGET=demux] %s <filename>\n", argv[0]);
            return 1;
    }

    return -vlc_demux_process_path(&args, filename);
}