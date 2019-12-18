#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  ParseLine (TYPE_1__*,char*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* vlc_stream_ReadLine (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux ( demux_t *p_demux )
{
    char            *psz_line;

    while( ( psz_line = vlc_stream_ReadLine( p_demux->s ) ) )
    {
        ParseLine( p_demux, psz_line );
        free( psz_line );
    }
    return VLC_SUCCESS;
}