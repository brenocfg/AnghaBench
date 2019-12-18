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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ demux_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int) ; 
 int vlc_stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ReSynch( demux_t *p_demux )
{
    for( ;; )
    {
        const uint8_t *p_peek;
        int i_peek = vlc_stream_Peek( p_demux->s, &p_peek, 1024 );
        if( i_peek < 8 )
            break;

        int i_skip = 0;

        while( i_skip < i_peek - 4 )
        {
            if( !memcmp( p_peek, "NSVf", 4 )
             || !memcmp( p_peek, "NSVs", 4 ) )
            {
                if( i_skip > 0
                 && vlc_stream_Read( p_demux->s, NULL, i_skip ) < i_skip )
                    return VLC_EGENERIC;
                return VLC_SUCCESS;
            }
            p_peek++;
            i_skip++;
        }

        if( vlc_stream_Read( p_demux->s, NULL, i_skip ) < i_skip )
            break;
    }
    return VLC_EGENERIC;
}