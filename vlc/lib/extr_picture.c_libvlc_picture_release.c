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
struct TYPE_4__ {scalar_t__ converted; int /*<<< orphan*/  fmt; int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ libvlc_picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 

void libvlc_picture_release( libvlc_picture_t* pic )
{
    if ( vlc_atomic_rc_dec( &pic->rc ) == false )
        return;
    video_format_Clean( &pic->fmt );
    if ( pic->converted )
        block_Release( pic->converted );
    free( pic );
}