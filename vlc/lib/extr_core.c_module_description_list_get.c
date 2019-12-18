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
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_4__ {struct TYPE_4__* p_next; int /*<<< orphan*/ * psz_help; int /*<<< orphan*/ * psz_longname; int /*<<< orphan*/ * psz_shortname; int /*<<< orphan*/ * psz_name; } ;
typedef  TYPE_1__ libvlc_module_description_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_module_description_list_release (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 scalar_t__ malloc (int) ; 
 char* module_get_help (int /*<<< orphan*/ *) ; 
 char* module_get_name (int /*<<< orphan*/ *,int) ; 
 char* module_get_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_list_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** module_list_get (size_t*) ; 
 int /*<<< orphan*/  module_provides (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static libvlc_module_description_t *module_description_list_get(
                libvlc_instance_t *p_instance, const char *capability )
{
    libvlc_module_description_t *p_list = NULL,
                          *p_actual = NULL,
                          *p_previous = NULL;
    size_t count;
    module_t **module_list = module_list_get( &count );

    for (size_t i = 0; i < count; i++)
    {
        module_t *p_module = module_list[i];

        if ( !module_provides( p_module, capability ) )
            continue;

        p_actual = ( libvlc_module_description_t * ) malloc( sizeof( libvlc_module_description_t ) );
        if ( p_actual == NULL )
        {
            libvlc_printerr( "Not enough memory" );
            libvlc_module_description_list_release( p_list );
            module_list_free( module_list );
            return NULL;
        }

        if ( p_list == NULL )
            p_list = p_actual;

        const char* name = module_get_object( p_module );
        const char* shortname = module_get_name( p_module, false );
        const char* longname = module_get_name( p_module, true );
        const char* help = module_get_help( p_module );
        p_actual->psz_name = name ? strdup( name ) : NULL;
        p_actual->psz_shortname = shortname ? strdup( shortname ) : NULL;
        p_actual->psz_longname = longname ? strdup( longname ) : NULL;
        p_actual->psz_help = help ? strdup( help ) : NULL;

        p_actual->p_next = NULL;
        if ( p_previous )
            p_previous->p_next = p_actual;
        p_previous = p_actual;
    }

    module_list_free( module_list );
    VLC_UNUSED( p_instance );
    return p_list;
}