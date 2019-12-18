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
typedef  int scan_modulation_t ;

/* Variables and functions */
#define  SCAN_MODULATION_APSK_16 142 
#define  SCAN_MODULATION_APSK_32 141 
#define  SCAN_MODULATION_AUTO 140 
#define  SCAN_MODULATION_DQPSK 139 
#define  SCAN_MODULATION_PSK_8 138 
#define  SCAN_MODULATION_QAM_128 137 
#define  SCAN_MODULATION_QAM_16 136 
#define  SCAN_MODULATION_QAM_256 135 
#define  SCAN_MODULATION_QAM_32 134 
#define  SCAN_MODULATION_QAM_4NR 133 
#define  SCAN_MODULATION_QAM_64 132 
#define  SCAN_MODULATION_QAM_AUTO 131 
#define  SCAN_MODULATION_QPSK 130 
#define  SCAN_MODULATION_VSB_16 129 
#define  SCAN_MODULATION_VSB_8 128 

const char *scan_value_modulation( scan_modulation_t m )
{
    switch(m)
    {
        case SCAN_MODULATION_QAM_16:     return "16QAM";
        case SCAN_MODULATION_QAM_32:     return "32QAM";
        case SCAN_MODULATION_QAM_64:     return "64QAM";
        case SCAN_MODULATION_QAM_128:    return "128QAM";
        case SCAN_MODULATION_QAM_256:    return "256QAM";
        case SCAN_MODULATION_QAM_AUTO:   return "QAM";
        case SCAN_MODULATION_PSK_8:      return "8PSK";
        case SCAN_MODULATION_QPSK:       return "QPSK";
        case SCAN_MODULATION_DQPSK:      return "DQPSK";
        case SCAN_MODULATION_APSK_16:    return "16APSK";
        case SCAN_MODULATION_APSK_32:    return "32APSK";
        case SCAN_MODULATION_VSB_8:      return "8VSB";
        case SCAN_MODULATION_VSB_16:     return "16VSB";
        case SCAN_MODULATION_QAM_4NR:
        case SCAN_MODULATION_AUTO:
        default:                        return "";
    }
}