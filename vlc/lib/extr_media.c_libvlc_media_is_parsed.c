#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int is_parsed; int /*<<< orphan*/  parsed_lock; } ;
typedef  TYPE_1__ libvlc_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

bool libvlc_media_is_parsed(libvlc_media_t *media)
{
    bool parsed;

    vlc_mutex_lock(&media->parsed_lock);
    parsed = media->is_parsed;
    vlc_mutex_unlock(&media->parsed_lock);
    return parsed;
}