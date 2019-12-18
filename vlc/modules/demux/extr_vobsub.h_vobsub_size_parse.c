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

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int sscanf (char const*,char*,int*,int*) ; 

__attribute__((used)) static inline int vobsub_size_parse( const char *psz_buf,
                                     int *pi_original_frame_width,
                                     int *pi_original_frame_height )
{
    int w, h;
    if( sscanf( psz_buf, "size: %dx%d", &w, &h ) == 2 )
    {
        *pi_original_frame_width = w;
        *pi_original_frame_height = h;
        return VLC_SUCCESS;
    }
    else
    {
        return VLC_EGENERIC;
    }
}