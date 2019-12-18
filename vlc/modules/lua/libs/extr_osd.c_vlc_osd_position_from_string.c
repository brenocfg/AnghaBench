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
#define  SUBPICTURE_ALIGN_BOTTOM 131 
#define  SUBPICTURE_ALIGN_LEFT 130 
#define  SUBPICTURE_ALIGN_RIGHT 129 
#define  SUBPICTURE_ALIGN_TOP 128 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static int vlc_osd_position_from_string( const char *psz_name )
{
    static const struct
    {
        int i_position;
        const char *psz_name;
    } pp_icons[] =
        { { 0,                                              "center"       },
          { SUBPICTURE_ALIGN_LEFT,                          "left"         },
          { SUBPICTURE_ALIGN_RIGHT,                         "right"        },
          { SUBPICTURE_ALIGN_TOP,                           "top"          },
          { SUBPICTURE_ALIGN_BOTTOM,                        "bottom"       },
          { SUBPICTURE_ALIGN_TOP   |SUBPICTURE_ALIGN_LEFT,  "top-left"     },
          { SUBPICTURE_ALIGN_TOP   |SUBPICTURE_ALIGN_RIGHT, "top-right"    },
          { SUBPICTURE_ALIGN_BOTTOM|SUBPICTURE_ALIGN_LEFT,  "bottom-left"  },
          { SUBPICTURE_ALIGN_BOTTOM|SUBPICTURE_ALIGN_RIGHT, "bottom-right" },
          { 0, NULL } };
    int i;
    for( i = 0; pp_icons[i].psz_name; i++ )
    {
        if( !strcmp( psz_name, pp_icons[i].psz_name ) )
            return pp_icons[i].i_position;
    }
    return 0;
}