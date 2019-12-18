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
struct TYPE_3__ {int /*<<< orphan*/  extra_tags; } ;
typedef  TYPE_1__ vlc_meta_t ;

/* Variables and functions */
 char* kVLCDictionaryNotFound ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  vlc_dictionary_insert (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dictionary_remove_value_for_key (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_meta_FreeExtraKey ; 

void vlc_meta_AddExtra( vlc_meta_t *m, const char *psz_name, const char *psz_value )
{
    char *psz_oldvalue = (char *)vlc_dictionary_value_for_key( &m->extra_tags, psz_name );
    if( psz_oldvalue != kVLCDictionaryNotFound )
        vlc_dictionary_remove_value_for_key( &m->extra_tags, psz_name,
                                            vlc_meta_FreeExtraKey, NULL );
    vlc_dictionary_insert( &m->extra_tags, psz_name, strdup(psz_value) );
}