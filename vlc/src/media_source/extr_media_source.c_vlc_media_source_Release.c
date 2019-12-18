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
typedef  int /*<<< orphan*/  vlc_media_source_t ;
struct TYPE_3__ {int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ media_source_private_t ;

/* Variables and functions */
 TYPE_1__* ms_priv (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_source_Delete (int /*<<< orphan*/ *) ; 

void
vlc_media_source_Release(vlc_media_source_t *ms)
{
    media_source_private_t *priv = ms_priv(ms);
    if (vlc_atomic_rc_dec(&priv->rc))
        vlc_media_source_Delete(ms);
}