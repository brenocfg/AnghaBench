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
 int /*<<< orphan*/  image_Type2Fourcc (char const*) ; 
 char* strrchr (char const*,char) ; 

vlc_fourcc_t image_Ext2Fourcc( const char *psz_name )
{
    psz_name = strrchr( psz_name, '.' );
    if( !psz_name ) return 0;
    psz_name++;

    return image_Type2Fourcc( psz_name );
}