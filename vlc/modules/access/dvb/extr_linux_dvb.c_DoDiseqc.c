#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_13__ {int* msg; } ;
struct TYPE_12__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; } ;
struct TYPE_11__ {int member_1; TYPE_2__ member_0; } ;
struct diseqc_cmd_t {int wait; TYPE_3__ cmd; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  scalar_t__ fe_sec_voltage_t ;
typedef  TYPE_3__* fe_sec_tone_mode_t ;
struct TYPE_14__ {int /*<<< orphan*/  i_frontend_handle; } ;
typedef  TYPE_4__ dvb_sys_t ;

/* Variables and functions */
 TYPE_3__* DecodeTone (int /*<<< orphan*/ *) ; 
 scalar_t__ DecodeVoltage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FE_DISEQC_SEND_BURST ; 
 int /*<<< orphan*/  FE_DISEQC_SEND_MASTER_CMD ; 
 int /*<<< orphan*/  FE_ENABLE_HIGH_LNB_VOLTAGE ; 
 int /*<<< orphan*/  FE_SET_TONE ; 
 int /*<<< orphan*/  FE_SET_VOLTAGE ; 
 TYPE_3__* SEC_MINI_A ; 
 TYPE_3__* SEC_MINI_B ; 
 TYPE_3__* SEC_TONE_OFF ; 
 TYPE_3__* SEC_TONE_ON ; 
 scalar_t__ SEC_VOLTAGE_13 ; 
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char*,...) ; 
 int var_GetBool (int /*<<< orphan*/ *,char*) ; 
 int var_GetInteger (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tick_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DoDiseqc( vlc_object_t *p_access, dvb_sys_t *p_sys )
{
    int i_val;
    bool b_val;
    int i_frequency, i_lnb_slof;
    fe_sec_voltage_t fe_voltage;
    fe_sec_tone_mode_t fe_tone;

    i_frequency = var_GetInteger( p_access, "dvb-frequency" );
    i_lnb_slof = var_GetInteger( p_access, "dvb-lnb-slof" );

    i_val = var_GetInteger( p_access, "dvb-tone" );
    if( i_val == -1 /* auto */ )
    {
        if( i_frequency >= i_lnb_slof )
            i_val = 1;
        else
            i_val = 0;
        var_SetInteger( p_access, "dvb-tone", i_val );
    }

    fe_voltage = DecodeVoltage( p_access );
    fe_tone = DecodeTone( p_access );

    /* Switch off continuous tone. */
    if( ioctl( p_sys->i_frontend_handle, FE_SET_TONE, SEC_TONE_OFF ) < 0 )
    {
        msg_Err( p_access, "switching tone %s error: %s", "off",
                 vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }

    /* Configure LNB voltage. */
    if( ioctl( p_sys->i_frontend_handle, FE_SET_VOLTAGE, fe_voltage ) < 0 )
    {
        msg_Err( p_access, "voltage error: %s", vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }

    b_val = var_GetBool( p_access, "dvb-high-voltage" );
    if( ioctl( p_sys->i_frontend_handle,
               FE_ENABLE_HIGH_LNB_VOLTAGE, b_val ) < 0 && b_val )
    {
        msg_Err( p_access, "high LNB voltage error: %s",
                 vlc_strerror_c(errno) );
    }

    /* Wait for at least 15 ms. */
    vlc_tick_sleep(VLC_TICK_FROM_MS(15));

    i_val = var_GetInteger( p_access, "dvb-satno" );
    if( i_val > 0 && i_val < 5 )
    {
        /* digital satellite equipment control,
         * specification is available from http://www.eutelsat.com/
         */

        /* 1.x compatible equipment */
        struct diseqc_cmd_t cmd =  { {{0xe0, 0x10, 0x38, 0xf0, 0x00, 0x00}, 4}, 0 };

        /* param: high nibble: reset bits, low nibble set bits,
         * bits are: option, position, polarization, band
         */
        cmd.cmd.msg[3] = 0xf0 /* reset bits */
                          | (((i_val - 1) * 4) & 0xc)
                          | (fe_voltage == SEC_VOLTAGE_13 ? 0 : 2)
                          | (fe_tone == SEC_TONE_ON ? 1 : 0);

        if( ioctl( p_sys->i_frontend_handle, FE_DISEQC_SEND_MASTER_CMD,
                   &cmd.cmd ) )
        {
            msg_Err( p_access, "master command sending error: %s",
                     vlc_strerror_c(errno) );
            return VLC_EGENERIC;
        }

        vlc_tick_sleep(VLC_TICK_FROM_MS(15 + cmd.wait));

        /* A or B simple diseqc ("diseqc-compatible") */
        if( ioctl( p_sys->i_frontend_handle, FE_DISEQC_SEND_BURST,
                  ((i_val - 1) % 2) ? SEC_MINI_B : SEC_MINI_A ) )
        {
            msg_Err( p_access, "burst sending error: %s",
                     vlc_strerror_c(errno) );
            return VLC_EGENERIC;
        }

        vlc_tick_sleep(VLC_TICK_FROM_MS(15));
    }

    if( ioctl( p_sys->i_frontend_handle, FE_SET_TONE, fe_tone ) )
    {
        msg_Err( p_access, "switching tone %s error: %s",
                 (fe_tone == SEC_TONE_ON) ? "on" : "off",
                 vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }

    vlc_tick_sleep(VLC_TICK_FROM_MS(50));
    return 0;
}