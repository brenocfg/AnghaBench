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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_FOURCC (char const,char const,char const,char const) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  vlc_fourcc_GetCodec (int,int /*<<< orphan*/ ) ; 

vlc_fourcc_t vlc_fourcc_GetCodecFromString( int i_cat, const char *psz_fourcc )
{
    if( !psz_fourcc || strlen(psz_fourcc) != 4 )
        return 0;
    return vlc_fourcc_GetCodec( i_cat,
                                VLC_FOURCC( psz_fourcc[0], psz_fourcc[1],
                                            psz_fourcc[2], psz_fourcc[3] ) );
}