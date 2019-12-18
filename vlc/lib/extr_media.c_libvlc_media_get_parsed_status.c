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
struct TYPE_3__ {int /*<<< orphan*/  parsed_lock; int /*<<< orphan*/  parsed_status; } ;
typedef  TYPE_1__ libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_media_parsed_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

libvlc_media_parsed_status_t
libvlc_media_get_parsed_status(libvlc_media_t *media)
{
    libvlc_media_parsed_status_t status;

    vlc_mutex_lock(&media->parsed_lock);
    status = media->parsed_status;
    vlc_mutex_unlock(&media->parsed_lock);
    return status;
}