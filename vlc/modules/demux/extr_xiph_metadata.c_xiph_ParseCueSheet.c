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
typedef  int /*<<< orphan*/  vlc_meta_t ;
typedef  int /*<<< orphan*/  seekpoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_APPEND (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strndup (char const*,int) ; 
 int /*<<< orphan*/  vlc_seekpoint_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xiph_ParseCueSheetMeta (unsigned int*,int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ ***,int /*<<< orphan*/ **,int*) ; 

__attribute__((used)) static void xiph_ParseCueSheet( unsigned *pi_flags, vlc_meta_t *p_meta,
                                const char *p_data, int i_data,
                                int *pi_seekpoint, seekpoint_t ***ppp_seekpoint )
{
    seekpoint_t *p_seekpoint = NULL;
    bool b_valid = false;

    const char *p_head = p_data;
    const char *p_tail = p_head;
    while( p_tail < p_data + i_data )
    {
        if( *p_tail == 0x0D )
        {
            char *psz = strndup( p_head, p_tail - p_head );
            if( psz )
            {
                xiph_ParseCueSheetMeta( pi_flags, p_meta, psz,
                                        pi_seekpoint, ppp_seekpoint,
                                        &p_seekpoint, &b_valid );
                free( psz );
            }
            if( *(++p_tail) == 0x0A )
                p_tail++;
            p_head = p_tail;
        }
        else
        {
            p_tail++;
        }
    }


    if( p_seekpoint )
    {
        if( b_valid )
            TAB_APPEND( *pi_seekpoint, *ppp_seekpoint, p_seekpoint );
        else
            vlc_seekpoint_Delete( p_seekpoint );
    }
}