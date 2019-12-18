#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;
struct TYPE_6__ {struct TYPE_6__* p_next; struct TYPE_6__* psz_description; struct TYPE_6__* psz_name; } ;
typedef  TYPE_1__ libvlc_audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_audio_output_list_release (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  module_get_name (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  module_get_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_list_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** module_list_get (size_t*) ; 
 int /*<<< orphan*/  module_provides (int /*<<< orphan*/ *,char*) ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

libvlc_audio_output_t *
        libvlc_audio_output_list_get( libvlc_instance_t *p_instance )
{
    size_t count;
    module_t **module_list = module_list_get( &count );
    libvlc_audio_output_t *list = NULL;

    for (size_t i = 0; i < count; i++)
    {
        module_t *module = module_list[i];

        if( !module_provides( module, "audio output" ) )
            continue;

        libvlc_audio_output_t *item = malloc( sizeof( *item ) );
        if( unlikely(item == NULL) )
        {
    error:
            libvlc_printerr( "Not enough memory" );
            libvlc_audio_output_list_release( list );
            list = NULL;
            break;
        }

        item->psz_name = strdup( module_get_object( module ) );
        item->psz_description = strdup( module_get_name( module, true ) );
        if( unlikely(item->psz_name == NULL || item->psz_description == NULL) )
        {
            free( item->psz_name );
            free( item->psz_description );
            free( item );
            goto error;
        }
        item->p_next = list;
        list = item;
    }
    module_list_free( module_list );

    VLC_UNUSED( p_instance );
    return list;
}