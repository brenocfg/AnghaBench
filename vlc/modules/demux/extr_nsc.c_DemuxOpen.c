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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_demux; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Demux ; 
 int /*<<< orphan*/  MAX_LINE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DemuxOpen( vlc_object_t * p_this )
{
    demux_t *p_demux = (demux_t *)p_this;
    const uint8_t *p_peek;
    int i_size;

    /* Lets check the content to see if this is a NSC file */
    i_size = vlc_stream_Peek( p_demux->s, &p_peek, MAX_LINE );
    i_size -= sizeof("NSC Format Version=") - 1;

    if ( i_size > 0 )
    {
        while ( i_size && strncasecmp( (char *)p_peek, "NSC Format Version=",
                                       (int) sizeof("NSC Format Version=") - 1 ) )
        {
            p_peek++;
            i_size--;
        }
        if ( !strncasecmp( (char *)p_peek, "NSC Format Version=",
                           (int) sizeof("NSC Format Version=") -1 ) )
        {
            p_demux->pf_demux = Demux;
            p_demux->pf_control = Control;
            return VLC_SUCCESS;
        }
    }
    return VLC_EGENERIC;
}