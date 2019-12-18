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
typedef  int /*<<< orphan*/  fe_sec_voltage_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_VOLTAGE_13 ; 
 int /*<<< orphan*/  SEC_VOLTAGE_18 ; 
 int /*<<< orphan*/  SEC_VOLTAGE_OFF ; 
 int var_GetInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static fe_sec_voltage_t DecodeVoltage( vlc_object_t *p_access )
{
    switch( var_GetInteger( p_access, "dvb-voltage" ) )
    {
        case 0:  return SEC_VOLTAGE_OFF;
        case 13: return SEC_VOLTAGE_13;
        case 18: return SEC_VOLTAGE_18;
        default: return SEC_VOLTAGE_OFF;
    }
}