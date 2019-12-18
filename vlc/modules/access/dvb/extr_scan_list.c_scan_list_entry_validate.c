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
struct TYPE_3__ {int delivery; int /*<<< orphan*/  i_bw; int /*<<< orphan*/  i_freq; int /*<<< orphan*/  i_rate; } ;
typedef  TYPE_1__ scan_list_entry_t ;

/* Variables and functions */
#define  SCAN_DELIVERY_DVB_C 134 
#define  SCAN_DELIVERY_DVB_S 133 
#define  SCAN_DELIVERY_DVB_S2 132 
#define  SCAN_DELIVERY_DVB_T 131 
#define  SCAN_DELIVERY_DVB_T2 130 
#define  SCAN_DELIVERY_ISDB_T 129 
#define  SCAN_DELIVERY_UNKNOWN 128 

__attribute__((used)) static bool scan_list_entry_validate( const scan_list_entry_t *p_entry )
{
    switch( p_entry->delivery )
    {
        case SCAN_DELIVERY_DVB_S:
        case SCAN_DELIVERY_DVB_S2:
        case SCAN_DELIVERY_DVB_C:
            return p_entry->i_freq && p_entry->i_rate;

        case SCAN_DELIVERY_DVB_T:
        case SCAN_DELIVERY_DVB_T2:
        case SCAN_DELIVERY_ISDB_T:
            return p_entry->i_freq && p_entry->i_bw;

        case SCAN_DELIVERY_UNKNOWN:
        default:
            break;
    }
    return false;
}