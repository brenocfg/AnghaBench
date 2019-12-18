#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_meta_type_t ;
typedef  int /*<<< orphan*/  vlc_meta_t ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  AppleNameToMeta (char const*,int const**,char const**) ; 
 int /*<<< orphan*/  AtomXA9ToMeta (int,int const**,char const**) ; 
 char* ExtractString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  vlc_meta_AddExtra (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  vlc_meta_Set (int /*<<< orphan*/ *,int const,char*) ; 

__attribute__((used)) static bool SetMeta( vlc_meta_t* p_meta, int i_type, char const* name, MP4_Box_t* p_box )
{
    vlc_meta_type_t const* type;
    char const* key;

    if( ( name != NULL && !AppleNameToMeta( name, &type, &key ) ) ||
        ( name == NULL && !AtomXA9ToMeta( i_type, &type, &key ) ) )
    {
        return false;
    }

    char* psz_utf = ExtractString( p_box );

    if( psz_utf )
    {
        if( type ) vlc_meta_Set( p_meta, *type, psz_utf );
        else       vlc_meta_AddExtra( p_meta, key, psz_utf );

        free( psz_utf );
    }

    return true;
}