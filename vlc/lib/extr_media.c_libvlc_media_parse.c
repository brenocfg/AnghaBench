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
typedef  int /*<<< orphan*/  libvlc_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_fetch_local ; 
 int /*<<< orphan*/  media_parse (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

void
libvlc_media_parse(libvlc_media_t *media)
{
    media_parse( media, false, libvlc_media_fetch_local, -1 );
}