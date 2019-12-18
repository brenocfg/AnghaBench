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
#define  OSD_HOR_SLIDER 129 
#define  OSD_VERT_SLIDER 128 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static int vlc_osd_slider_type_from_string( const char *psz_name )
{
    static const struct
    {
        int i_type;
        const char *psz_name;
    } pp_types[] =
        { { OSD_HOR_SLIDER, "horizontal" },
          { OSD_VERT_SLIDER, "vertical" },
          { 0, NULL } };
    int i;
    for( i = 0; pp_types[i].psz_name; i++ )
    {
        if( !strcmp( psz_name, pp_types[i].psz_name ) )
            return pp_types[i].i_type;
    }
    return 0;
}