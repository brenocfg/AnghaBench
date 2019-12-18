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
typedef  int /*<<< orphan*/  varname ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;
struct TYPE_4__ {char* psz_device; char* psz_description; struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ libvlc_audio_output_device_t ;

/* Variables and functions */
 scalar_t__ VLC_VAR_STRING ; 
 size_t config_GetPszChoices (char*,char***,char***) ; 
 scalar_t__ config_GetType (char*) ; 
 int /*<<< orphan*/  free (char**) ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ snprintf (char*,int,char*,char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

libvlc_audio_output_device_t *
libvlc_audio_output_device_list_get( libvlc_instance_t *p_instance,
                                     const char *aout )
{
    char varname[32];
    if( (size_t)snprintf( varname, sizeof(varname), "%s-audio-device", aout )
                                                           >= sizeof(varname) )
        return NULL;

    if( config_GetType(varname) != VLC_VAR_STRING )
        return NULL;

    libvlc_audio_output_device_t *list = NULL, **pp = &list;
    char **values, **texts;
    ssize_t count = config_GetPszChoices( varname, &values, &texts );
    for( ssize_t i = 0; i < count; i++ )
    {
        libvlc_audio_output_device_t *item = malloc( sizeof(*item) );
        if( unlikely(item == NULL) )
            break;

        *pp = item;
        pp = &item->p_next;
        item->psz_device = values[i];
        item->psz_description = texts[i];
    }

    *pp = NULL;
    free( texts );
    free( values );
    (void) p_instance;
    return list;
}