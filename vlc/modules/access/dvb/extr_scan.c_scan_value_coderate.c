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
typedef  int scan_coderate_t ;

/* Variables and functions */
#define  SCAN_CODERATE_1_2 138 
#define  SCAN_CODERATE_2_3 137 
#define  SCAN_CODERATE_3_4 136 
#define  SCAN_CODERATE_3_5 135 
#define  SCAN_CODERATE_4_5 134 
#define  SCAN_CODERATE_5_6 133 
#define  SCAN_CODERATE_7_8 132 
#define  SCAN_CODERATE_8_9 131 
#define  SCAN_CODERATE_9_10 130 
#define  SCAN_CODERATE_AUTO 129 
#define  SCAN_CODERATE_NONE 128 

const char *scan_value_coderate( scan_coderate_t c )
{
    switch( c )
    {
        case SCAN_CODERATE_NONE: return "0";
        case SCAN_CODERATE_1_2:  return "1/2";
        case SCAN_CODERATE_2_3:  return "2/3";
        case SCAN_CODERATE_3_4:  return "3/4";
        case SCAN_CODERATE_3_5:  return "3/5";
        case SCAN_CODERATE_4_5:  return "4/5";
        case SCAN_CODERATE_5_6:  return "5/6";
        case SCAN_CODERATE_7_8:  return "7/8";
        case SCAN_CODERATE_8_9:  return "8/9";
        case SCAN_CODERATE_9_10: return "9/10";
        case SCAN_CODERATE_AUTO:
        default:                 return "";
    }
}