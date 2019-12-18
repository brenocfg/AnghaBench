#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_2__ {scalar_t__ i_codec; int /*<<< orphan*/  psz_mime; } ;

/* Variables and functions */
 TYPE_1__* mime_table ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

vlc_fourcc_t image_Mime2Fourcc( const char *psz_mime )
{
    for( int i = 0; mime_table[i].i_codec; i++ )
        if( !strcmp( psz_mime, mime_table[i].psz_mime ) )
            return mime_table[i].i_codec;
    return 0;
}