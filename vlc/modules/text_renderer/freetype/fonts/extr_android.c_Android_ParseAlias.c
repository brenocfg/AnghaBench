#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xml_reader_t ;
typedef  int /*<<< orphan*/  vlc_family_t ;
typedef  int /*<<< orphan*/  vlc_dictionary_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_5__ {int /*<<< orphan*/  family_map; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 char* ToLower (char const*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char const*) ; 
 int /*<<< orphan*/  vlc_dictionary_insert (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char*) ; 
 char* xml_ReaderNextAttr (int /*<<< orphan*/ *,char const**) ; 

__attribute__((used)) static int Android_ParseAlias( filter_t *p_filter, xml_reader_t *p_xml )
{
    filter_sys_t     *p_sys       = p_filter->p_sys;
    vlc_dictionary_t *p_dict      = &p_sys->family_map;
    vlc_family_t     *p_dest      = NULL;
    char             *psz_name    = NULL;
    char             *psz_dest    = NULL;
    const char       *psz_val     = NULL;
    const char       *psz_attr    = NULL;
    int               i_weight    = 0;
    int               i_ret       = VLC_SUCCESS;

    while( ( psz_attr = xml_ReaderNextAttr( p_xml, &psz_val ) ) )
    {
        if( !strcasecmp( "weight", psz_attr ) && psz_val && *psz_val )
            i_weight = atoi( psz_val );
        else if( !strcasecmp( "to", psz_attr ) && psz_val && *psz_val )
            psz_dest = ToLower( psz_val );
        else if( !strcasecmp( "name", psz_attr ) && psz_val && *psz_val )
            psz_name = ToLower( psz_val );
    }

    if( !psz_dest || !psz_name )
    {
        i_ret = VLC_EGENERIC;
        goto done;
    }

    p_dest = vlc_dictionary_value_for_key( p_dict, psz_dest );

    if( p_dest && i_weight == 0 )
        if( vlc_dictionary_value_for_key( p_dict, psz_name ) == NULL )
            vlc_dictionary_insert( p_dict, psz_name, p_dest );

done:
    free( psz_dest );
    free( psz_name );
    return i_ret;
}