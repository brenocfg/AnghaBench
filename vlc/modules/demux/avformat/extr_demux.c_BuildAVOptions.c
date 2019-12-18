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
typedef  int /*<<< orphan*/  demux_t ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_av_get_options (char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static AVDictionary * BuildAVOptions( demux_t *p_demux )
{
    char *psz_opts = var_InheritString( p_demux, "avformat-options" );
    AVDictionary *options = NULL;
    if( psz_opts )
    {
        vlc_av_get_options( psz_opts, &options );
        free( psz_opts );
    }
    return options;
}