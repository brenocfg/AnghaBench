#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int i_size; TYPE_3__** p_entries; } ;
typedef  TYPE_2__ vlc_dictionary_t ;
struct TYPE_8__ {char* psz_key; char* p_value; struct TYPE_8__* p_next; } ;
typedef  TYPE_3__ vlc_dictionary_entry_t ;
struct TYPE_6__ {int /*<<< orphan*/  end; int /*<<< orphan*/  begin; } ;
struct TYPE_9__ {TYPE_1__ timings; TYPE_2__ attr_dict; } ;
typedef  TYPE_4__ tt_node_t ;
struct vlc_memstream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  tt_MemstreamPutEntities (struct vlc_memstream*,char const*) ; 
 char* tt_genTiming (int /*<<< orphan*/ ) ; 
 scalar_t__ tt_time_Valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_memstream_printf (struct vlc_memstream*,char*,char*) ; 
 int /*<<< orphan*/  vlc_memstream_putc (struct vlc_memstream*,char) ; 

__attribute__((used)) static void tt_node_AttributesToText( struct vlc_memstream *p_stream, const tt_node_t* p_node )
{
    bool b_timed_node = false;
    const vlc_dictionary_t* p_attr_dict = &p_node->attr_dict;
    for( int i = 0; i < p_attr_dict->i_size; ++i )
    {
        for ( vlc_dictionary_entry_t* p_entry = p_attr_dict->p_entries[i];
                                      p_entry != NULL; p_entry = p_entry->p_next )
        {
            const char *psz_value = NULL;

            if( !strcmp(p_entry->psz_key, "begin") ||
                !strcmp(p_entry->psz_key, "end") ||
                !strcmp(p_entry->psz_key, "dur") )
            {
                b_timed_node = true;
                /* will remove duration */
                continue;
            }
            else if( !strcmp(p_entry->psz_key, "timeContainer") )
            {
                /* also remove sequential timings info (all abs now) */
                continue;
            }
            else
            {
                psz_value = p_entry->p_value;
            }

            if( psz_value == NULL )
                continue;

            vlc_memstream_printf( p_stream, " %s=\"", p_entry->psz_key );
            tt_MemstreamPutEntities( p_stream, psz_value );
            vlc_memstream_putc( p_stream, '"' );
        }
    }

    if( b_timed_node )
    {
        if( tt_time_Valid( &p_node->timings.begin ) )
        {
            char *psz = tt_genTiming( p_node->timings.begin );
            vlc_memstream_printf( p_stream, " begin=\"%s\"", psz );
            free( psz );
        }

        if( tt_time_Valid( &p_node->timings.end ) )
        {
            char *psz = tt_genTiming( p_node->timings.end );
            vlc_memstream_printf( p_stream, " end=\"%s\"", psz );
            free( psz );
        }
    }
}