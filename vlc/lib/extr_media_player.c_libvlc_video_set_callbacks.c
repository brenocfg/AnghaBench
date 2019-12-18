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
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  var_SetAddress (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 

void libvlc_video_set_callbacks( libvlc_media_player_t *mp,
    void *(*lock_cb) (void *, void **),
    void (*unlock_cb) (void *, void *, void *const *),
    void (*display_cb) (void *, void *),
    void *opaque )
{
    var_SetAddress( mp, "vmem-lock", lock_cb );
    var_SetAddress( mp, "vmem-unlock", unlock_cb );
    var_SetAddress( mp, "vmem-display", display_cb );
    var_SetAddress( mp, "vmem-data", opaque );
    var_SetString( mp, "dec-dev", "none" );
    var_SetString( mp, "vout", "vmem" );
    var_SetString( mp, "window", "dummy" );
}