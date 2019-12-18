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
struct TYPE_3__ {char member_0; int /*<<< orphan*/  const member_1; } ;
typedef  TYPE_1__ dvb_int_map_t ;

/* Variables and functions */
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int dvb_parse_int (char,TYPE_1__ const*,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static unsigned dvb_parse_polarization (char pol)
{
    static const dvb_int_map_t tab[5] = {
        { 0,   SEC_VOLTAGE_OFF },
        { 'H', SEC_VOLTAGE_18  },
        { 'L', SEC_VOLTAGE_18  },
        { 'R', SEC_VOLTAGE_13  },
        { 'V', SEC_VOLTAGE_13  },
    };
    return dvb_parse_int (pol, tab, 5, SEC_VOLTAGE_OFF);
}