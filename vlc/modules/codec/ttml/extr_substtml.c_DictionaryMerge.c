#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int i_size; TYPE_2__** p_entries; } ;
typedef  TYPE_1__ vlc_dictionary_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_value; int /*<<< orphan*/  psz_key; struct TYPE_9__* p_next; } ;
typedef  TYPE_2__ vlc_dictionary_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vlc_dictionary_has_key (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dictionary_insert (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dictionary_remove_value_for_key (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DictionaryMerge( const vlc_dictionary_t *p_src, vlc_dictionary_t *p_dst,
                             bool b_override )
{
    for( int i = 0; i < p_src->i_size; ++i )
    {
        for ( const vlc_dictionary_entry_t* p_entry = p_src->p_entries[i];
                                            p_entry != NULL; p_entry = p_entry->p_next )
        {
            if( !strncmp( "tts:", p_entry->psz_key, 4 ) ||
                !strncmp( "ttp:", p_entry->psz_key, 4 ) ||
                !strcmp( "xml:space", p_entry->psz_key ) )
            {
                if( vlc_dictionary_has_key( p_dst, p_entry->psz_key ) )
                {
                    if( b_override )
                    {
                        vlc_dictionary_remove_value_for_key( p_dst, p_entry->psz_key, NULL, NULL );
                        vlc_dictionary_insert( p_dst, p_entry->psz_key, p_entry->p_value );
                    }
                }
                else
                    vlc_dictionary_insert( p_dst, p_entry->psz_key, p_entry->p_value );
            }
        }
    }
}