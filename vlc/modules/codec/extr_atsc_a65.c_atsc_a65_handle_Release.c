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
struct TYPE_4__ {struct TYPE_4__* psz_lang; scalar_t__ iconv_u16be; } ;
typedef  TYPE_1__ atsc_a65_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_iconv_close (scalar_t__) ; 

void atsc_a65_handle_Release( atsc_a65_handle_t *p_handle )
{
    if( p_handle->iconv_u16be )
        vlc_iconv_close( p_handle->iconv_u16be );
    free( p_handle->psz_lang );
    free( p_handle );
}