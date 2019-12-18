#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {int type; int caps; int /*<<< orphan*/  notifier_delay; int /*<<< orphan*/  symbol_rate_tolerance; int /*<<< orphan*/  symbol_rate_max; int /*<<< orphan*/  symbol_rate_min; int /*<<< orphan*/  frequency_tolerance; int /*<<< orphan*/  frequency_stepsize; int /*<<< orphan*/  frequency_max; int /*<<< orphan*/  frequency_min; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_3__ info; } ;
typedef  TYPE_1__ frontend_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_frontend_handle; TYPE_1__* p_frontend; } ;
typedef  TYPE_2__ dvb_sys_t ;

/* Variables and functions */
#define  FE_ATSC 133 
 int FE_CAN_16VSB ; 
 int FE_CAN_2G_MODULATION ; 
 int FE_CAN_8VSB ; 
 int FE_CAN_BANDWIDTH_AUTO ; 
 int FE_CAN_FEC_1_2 ; 
 int FE_CAN_FEC_2_3 ; 
 int FE_CAN_FEC_3_4 ; 
 int FE_CAN_FEC_4_5 ; 
 int FE_CAN_FEC_5_6 ; 
 int FE_CAN_FEC_6_7 ; 
 int FE_CAN_FEC_7_8 ; 
 int FE_CAN_FEC_8_9 ; 
 int FE_CAN_FEC_AUTO ; 
 int FE_CAN_GUARD_INTERVAL_AUTO ; 
 int FE_CAN_HIERARCHY_AUTO ; 
 int FE_CAN_INVERSION_AUTO ; 
 int FE_CAN_MUTE_TS ; 
 int FE_CAN_QAM_128 ; 
 int FE_CAN_QAM_16 ; 
 int FE_CAN_QAM_256 ; 
 int FE_CAN_QAM_32 ; 
 int FE_CAN_QAM_64 ; 
 int FE_CAN_QAM_AUTO ; 
 int FE_CAN_QPSK ; 
 int FE_CAN_RECOVER ; 
 int FE_CAN_TRANSMISSION_MODE_AUTO ; 
 int FE_CAN_TURBO_FEC ; 
 int /*<<< orphan*/  FE_GET_INFO ; 
 int FE_HAS_EXTENDED_CAPS ; 
 int FE_IS_STUPID ; 
#define  FE_MEMORY 132 
#define  FE_NET 131 
#define  FE_OFDM 130 
#define  FE_QAM 129 
#define  FE_QPSK 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int) ; 
 int vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int FrontendInfo( vlc_object_t *p_access, dvb_sys_t *p_sys )
{
    frontend_t *p_frontend = p_sys->p_frontend;

    /* Determine type of frontend */
    if( ioctl( p_sys->i_frontend_handle, FE_GET_INFO, &p_frontend->info ) < 0 )
    {
        msg_Err( p_access, "frontend info request error: %s",
                 vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }

    /* Print out frontend capabilities. */
    msg_Dbg(p_access, "Frontend Info:" );
    msg_Dbg(p_access, "  name = %s", p_frontend->info.name );
    switch( p_frontend->info.type )
    {
        case FE_QPSK:
            msg_Dbg( p_access, "  type = QPSK (DVB-S)" );
            break;
        case FE_QAM:
            msg_Dbg( p_access, "  type = QAM (DVB-C)" );
            break;
        case FE_OFDM:
            msg_Dbg( p_access, "  type = OFDM (DVB-T)" );
            break;
        case FE_ATSC:
            msg_Dbg( p_access, "  type = ATSC (USA)" );
            break;
#if 0 /* DVB_API_VERSION == 3 */
        case FE_MEMORY:
            msg_Dbg( p_access, "  type = MEMORY" );
            break;
        case FE_NET:
            msg_Dbg( p_access, "  type = NETWORK" );
            break;
#endif
        default:
            msg_Err( p_access, "  unknown frontend type (%d)",
                     p_frontend->info.type );
            return VLC_EGENERIC;
    }
    msg_Dbg(p_access, "  frequency_min = %u (kHz)",
            p_frontend->info.frequency_min);
    msg_Dbg(p_access, "  frequency_max = %u (kHz)",
            p_frontend->info.frequency_max);
    msg_Dbg(p_access, "  frequency_stepsize = %u",
            p_frontend->info.frequency_stepsize);
    msg_Dbg(p_access, "  frequency_tolerance = %u",
            p_frontend->info.frequency_tolerance);
    msg_Dbg(p_access, "  symbol_rate_min = %u (kHz)",
            p_frontend->info.symbol_rate_min);
    msg_Dbg(p_access, "  symbol_rate_max = %u (kHz)",
            p_frontend->info.symbol_rate_max);
    msg_Dbg(p_access, "  symbol_rate_tolerance (ppm) = %u",
            p_frontend->info.symbol_rate_tolerance);
    msg_Dbg(p_access, "  notifier_delay (ms) = %u",
            p_frontend->info.notifier_delay );

    msg_Dbg(p_access, "Frontend Info capability list:");
    if( p_frontend->info.caps == FE_IS_STUPID)
        msg_Dbg(p_access, "  no capabilities - frontend is stupid!");
    if( p_frontend->info.caps & FE_CAN_INVERSION_AUTO)
        msg_Dbg(p_access, "  inversion auto");
    if( p_frontend->info.caps & FE_CAN_FEC_1_2)
        msg_Dbg(p_access, "  forward error correction 1/2");
    if( p_frontend->info.caps & FE_CAN_FEC_2_3)
        msg_Dbg(p_access, "  forward error correction 2/3");
    if( p_frontend->info.caps & FE_CAN_FEC_3_4)
        msg_Dbg(p_access, "  forward error correction 3/4");
    if( p_frontend->info.caps & FE_CAN_FEC_4_5)
        msg_Dbg(p_access, "  forward error correction 4/5");
    if( p_frontend->info.caps & FE_CAN_FEC_5_6)
        msg_Dbg(p_access, "  forward error correction 5/6");
    if( p_frontend->info.caps & FE_CAN_FEC_6_7)
        msg_Dbg(p_access, "  forward error correction 6/7");
    if( p_frontend->info.caps & FE_CAN_FEC_7_8)
        msg_Dbg(p_access, "  forward error correction 7/8");
    if( p_frontend->info.caps & FE_CAN_FEC_8_9)
        msg_Dbg(p_access, "  forward error correction 8/9");
    if( p_frontend->info.caps & FE_CAN_FEC_AUTO)
        msg_Dbg(p_access, "  forward error correction auto");
    if( p_frontend->info.caps & FE_CAN_QPSK)
        msg_Dbg(p_access, "  QPSK modulation");
    if( p_frontend->info.caps & FE_CAN_QAM_16)
        msg_Dbg(p_access, "  QAM 16 modulation");
    if( p_frontend->info.caps & FE_CAN_QAM_32)
        msg_Dbg(p_access, "  QAM 32 modulation");
    if( p_frontend->info.caps & FE_CAN_QAM_64)
        msg_Dbg(p_access, "  QAM 64 modulation");
    if( p_frontend->info.caps & FE_CAN_QAM_128)
        msg_Dbg(p_access, "  QAM 128 modulation");
    if( p_frontend->info.caps & FE_CAN_QAM_256)
        msg_Dbg(p_access, "  QAM 256 modulation");
    if( p_frontend->info.caps & FE_CAN_QAM_AUTO)
        msg_Dbg(p_access, "  QAM auto modulation");
    if( p_frontend->info.caps & FE_CAN_TRANSMISSION_MODE_AUTO)
        msg_Dbg(p_access, "  transmission mode auto");
    if( p_frontend->info.caps & FE_CAN_BANDWIDTH_AUTO)
        msg_Dbg(p_access, "  bandwidth mode auto");
    if( p_frontend->info.caps & FE_CAN_GUARD_INTERVAL_AUTO)
        msg_Dbg(p_access, "  guard interval mode auto");
    if( p_frontend->info.caps & FE_CAN_HIERARCHY_AUTO)
        msg_Dbg(p_access, "  hierarchy mode auto");
    if( p_frontend->info.caps & FE_CAN_8VSB)
        msg_Dbg(p_access, "  8-level VSB modulation");
    if( p_frontend->info.caps & FE_CAN_16VSB)
        msg_Dbg(p_access, "  16-level VSB modulation");
    if( p_frontend->info.caps & FE_HAS_EXTENDED_CAPS)
        msg_Dbg(p_access, "  extended capabilities");
    /* 3 capabilities that don't exist yet HERE */
#if (DVB_API_VERSION > 5) \
 || ((DVB_API_VERSION == 5 && DVB_API_VERSION_MINOR >= 2))
    if( p_frontend->info.caps & FE_CAN_TURBO_FEC)
        msg_Dbg(p_access, "  Turbo FEC modulation");
#else
# warning Please update your Linux kernel headers!
#endif
    if( p_frontend->info.caps & FE_CAN_2G_MODULATION)
        msg_Dbg(p_access, "  2nd generation modulation (DVB-S2)");
    /* FE_NEEDS_BENDING is deprecated */
    if( p_frontend->info.caps & FE_CAN_RECOVER)
        msg_Dbg(p_access, "  cable unplug recovery");
    if( p_frontend->info.caps & FE_CAN_MUTE_TS)
        msg_Dbg(p_access, "  spurious TS muting");
   msg_Dbg(p_access, "End of capability list");

    return VLC_SUCCESS;
}