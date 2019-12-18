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
struct TYPE_3__ {scalar_t__ e_wellknowntype; } ;
typedef  TYPE_1__ MP4_Box_data_data_t ;

/* Variables and functions */
 scalar_t__ DATA_WKT_BMP ; 
 scalar_t__ DATA_WKT_JPEG ; 
 scalar_t__ DATA_WKT_PNG ; 

__attribute__((used)) static bool imageTypeCompatible( const MP4_Box_data_data_t *p_data )
{
    return p_data && (
    p_data->e_wellknowntype == DATA_WKT_PNG ||
    p_data->e_wellknowntype == DATA_WKT_JPEG ||
    p_data->e_wellknowntype == DATA_WKT_BMP );
}