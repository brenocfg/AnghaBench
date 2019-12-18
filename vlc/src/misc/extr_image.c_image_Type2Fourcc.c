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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_codec; int /*<<< orphan*/  psz_ext; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* ext_table ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

vlc_fourcc_t image_Type2Fourcc( const char *psz_type )
{
    for( unsigned i = 0; i < ARRAY_SIZE(ext_table); i++ )
        if( !strcasecmp( ext_table[i].psz_ext, psz_type ) )
            return ext_table[i].i_codec;

    return 0;
}