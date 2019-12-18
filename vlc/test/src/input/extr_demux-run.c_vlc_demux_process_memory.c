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
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/ * libvlc_create (struct vlc_run_args const*) ; 
 int libvlc_demux_process_memory (int /*<<< orphan*/ *,struct vlc_run_args const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 

int vlc_demux_process_memory(const struct vlc_run_args *args,
                             const unsigned char *buf, size_t length)
{
    libvlc_instance_t *vlc = libvlc_create(args);
    if (vlc == NULL)
        return -1;

    int ret = libvlc_demux_process_memory(vlc, args, buf, length);
    libvlc_release(vlc);
    return ret;
}