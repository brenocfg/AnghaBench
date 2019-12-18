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
 int /*<<< orphan*/ * libvlc_new (int,char const* const*) ; 

__attribute__((used)) static libvlc_instance_t *create_libvlc(void)
{
    static const char* const args[] = {
        "--intf", "dummy",                  /* no interface                   */
        "--vout", "dummy",                  /* we don't want video (output)   */
        "--no-audio",                       /* we don't want audio (decoding) */
        "--no-video-title-show",            /* nor the filename displayed     */
        "--no-stats",                       /* no stats                       */
        "--no-sub-autodetect-file",         /* we don't want subtitles        */
        "--no-inhibit",                     /* we don't want interfaces       */
        "--no-disable-screensaver",         /* we don't want interfaces       */
        "--no-snapshot-preview",            /* no blending in dummy vout      */
#ifndef NDEBUG
        "--verbose=2",                      /* full log                       */
#endif
    };

    return libvlc_new(sizeof args / sizeof *args, args);
}