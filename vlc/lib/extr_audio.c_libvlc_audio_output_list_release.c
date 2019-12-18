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
struct TYPE_4__ {struct TYPE_4__* psz_description; struct TYPE_4__* psz_name; struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ libvlc_audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void libvlc_audio_output_list_release( libvlc_audio_output_t *list )
{
    while( list != NULL )
    {
        libvlc_audio_output_t *next = list->p_next;

        free( list->psz_name );
        free( list->psz_description );
        free( list );
        list = next;
    }
}