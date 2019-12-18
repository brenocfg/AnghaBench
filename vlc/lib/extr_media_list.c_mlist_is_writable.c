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
struct TYPE_3__ {scalar_t__ b_read_only; } ;
typedef  TYPE_1__ libvlc_media_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc_printerr (char*) ; 

__attribute__((used)) static inline
bool mlist_is_writable( libvlc_media_list_t *p_mlist )
{
    if( !p_mlist||p_mlist->b_read_only )
    {
        /* We are read-only from user side */
        libvlc_printerr( "Attempt to write a read-only media list" );
        return false;
    }
    return true;
}