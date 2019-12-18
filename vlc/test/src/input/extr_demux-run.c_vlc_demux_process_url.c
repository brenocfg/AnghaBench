#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vlc_run_args {int dummy; } ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_libvlc_int; } ;
typedef  TYPE_1__ libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int demux_process_stream (struct vlc_run_args const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__* libvlc_create (struct vlc_run_args const*) ; 
 int /*<<< orphan*/  libvlc_release (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * vlc_access_NewMRL (int /*<<< orphan*/ ,char const*) ; 

int vlc_demux_process_url(const struct vlc_run_args *args, const char *url)
{
    libvlc_instance_t *vlc = libvlc_create(args);
    if (vlc == NULL)
        return -1;

    stream_t *s = vlc_access_NewMRL(VLC_OBJECT(vlc->p_libvlc_int), url);
    if (s == NULL)
        fprintf(stderr, "Error: cannot create input stream: %s\n", url);

    int ret = demux_process_stream(args, s);
    libvlc_release(vlc);
    return ret;
}