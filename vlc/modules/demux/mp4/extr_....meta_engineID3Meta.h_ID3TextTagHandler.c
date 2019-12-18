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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 char* ID3TextConvert (int /*<<< orphan*/  const*,size_t,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  vlc_meta_AddExtra (int /*<<< orphan*/ *,char const*,char const*) ; 
 char* vlc_meta_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* vlc_meta_GetExtra (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_meta_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool ID3TextTagHandler( const uint8_t *p_buf, size_t i_buf,
                               vlc_meta_type_t type, const char *psz_extra,
                               vlc_meta_t *p_meta, bool *pb_updated )
{
    if( p_meta == NULL )
        return false;

    char *p_alloc;
    const char *psz = ID3TextConvert( p_buf, i_buf, &p_alloc );
    if( psz && *psz )
    {
        const char *psz_old = ( psz_extra ) ? vlc_meta_GetExtra( p_meta, psz_extra ):
                                              vlc_meta_Get( p_meta, type );
        if( !psz_old || strcmp( psz_old, psz ) )
        {
            if( pb_updated )
                *pb_updated = true;
            if( psz_extra )
                vlc_meta_AddExtra( p_meta, psz_extra, psz );
            else
                vlc_meta_Set( p_meta, type, psz );
        }
    }
    free( p_alloc );

    return (psz != NULL);
}