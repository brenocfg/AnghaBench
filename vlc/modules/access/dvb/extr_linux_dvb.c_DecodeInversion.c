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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  fe_spectral_inversion_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVERSION_AUTO ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int var_GetInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static fe_spectral_inversion_t DecodeInversion( vlc_object_t *p_access )
{
    int i_val;
    fe_spectral_inversion_t fe_inversion = 0;

    i_val = var_GetInteger( p_access, "dvb-inversion" );
    msg_Dbg( p_access, "using inversion=%d", i_val );

    switch( i_val )
    {
        case 0: fe_inversion = INVERSION_OFF; break;
        case 1: fe_inversion = INVERSION_ON; break;
        case 2: fe_inversion = INVERSION_AUTO; break;
        default:
            msg_Dbg( p_access, "dvb has inversion not set, using auto");
            fe_inversion = INVERSION_AUTO;
            break;
    }
    return fe_inversion;
}