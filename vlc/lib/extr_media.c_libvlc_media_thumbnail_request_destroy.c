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
struct TYPE_4__ {int /*<<< orphan*/  md; } ;
typedef  TYPE_1__ libvlc_media_thumbnail_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ ) ; 

void libvlc_media_thumbnail_request_destroy( libvlc_media_thumbnail_request_t *req )
{
    libvlc_media_release( req->md );
    free( req );
}