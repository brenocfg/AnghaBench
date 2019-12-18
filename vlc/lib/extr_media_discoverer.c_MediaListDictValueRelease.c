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

/* Variables and functions */
 int /*<<< orphan*/  libvlc_media_list_release (void*) ; 

__attribute__((used)) static void
MediaListDictValueRelease( void* mlist, void* obj )
{
    libvlc_media_list_release( mlist );
    (void)obj;
}