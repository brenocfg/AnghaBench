#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  psz_channel_number; int /*<<< orphan*/  psz_channel_call_letter; int /*<<< orphan*/  psz_channel_name; } ;
struct TYPE_8__ {int i_type; TYPE_1__ meta; } ;
typedef  TYPE_2__ xds_t ;
struct TYPE_9__ {int i_data; int /*<<< orphan*/ * p_data; } ;
typedef  TYPE_3__ xds_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  XdsChangeString (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  XdsStringUtf8 (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void XdsDecodeChannel( xds_t *h, xds_packet_t *pk )
{
    char name[2*32+1];
    char chan[2*32+1];

    switch( h->i_type )
    {
    case 0x01:
        if( pk->i_data < 2 )
            return;
        XdsStringUtf8( name, pk->p_data, pk->i_data );
        if( XdsChangeString( h, &h->meta.psz_channel_name, name ) )
        {
            //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Channel (Network Name) %d'\n", pk->i_data );
            //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: ====> %s\n", name );
        }
        break;

    case 0x02:
        if( pk->i_data < 4 )
            return;

        XdsStringUtf8( name, pk->p_data, 4 );
        if( XdsChangeString( h, &h->meta.psz_channel_call_letter, name ) )
        {
            //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Channel (Network Call Letter)' %d\n", pk->i_data );
            //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: ====> call letter %s\n", name );
        }
        if( pk->i_data >= 6 )
        {
            XdsStringUtf8( chan, &pk->p_data[4], 2 );
            if( XdsChangeString( h, &h->meta.psz_channel_number, chan ) )
            {
                //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Channel (Network Call Letter)' %d\n", pk->i_data );
                //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: ====> channel number %s\n", chan );
            }
        }
        else
        {
            if( XdsChangeString( h, &h->meta.psz_channel_number, NULL ) )
            {
                //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Channel (Network Call Letter)' %d\n", pk->i_data );
                //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: ====> no channel number letter anymore\n" );
            }
        }
        break;
    case 0x03:
        //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Channel (Channel Tape Delay)'\n" );
        break;
    case 0x04:
        //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Channel (Transmission Signal Identifier)'\n" );
        break;
    default:
#ifdef TY_XDS_DEBUG
        fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Channel (Unknown 0x%x)'\n", h->i_type );
#endif
        break;
    }
}