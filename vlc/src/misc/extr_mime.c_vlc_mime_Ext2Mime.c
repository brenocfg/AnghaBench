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
struct TYPE_2__ {char const* psz_mime; scalar_t__* psz_ext; } ;

/* Variables and functions */
 TYPE_1__* ext_mime ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__*,char*) ; 
 char* strrchr (char const*,char) ; 

const char *vlc_mime_Ext2Mime( const char *psz_url )
{

    char *psz_ext;

    psz_ext = strrchr( psz_url, '.' );
    if( psz_ext )
    {
        int i;

        for( i = 0; ext_mime[i].psz_ext[0] ; i++ )
        {
            if( !strcasecmp( ext_mime[i].psz_ext, psz_ext ) )
            {
                return ext_mime[i].psz_mime;
            }
        }
    }
    return "application/octet-stream";
}