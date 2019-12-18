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

/* Variables and functions */
#define  GPU_MANUFACTURER_AMD 133 
#define  GPU_MANUFACTURER_INTEL 132 
#define  GPU_MANUFACTURER_NVIDIA 131 
#define  GPU_MANUFACTURER_QUALCOMM 130 
#define  GPU_MANUFACTURER_S3 129 
#define  GPU_MANUFACTURER_VIA 128 

const char *DxgiVendorStr(unsigned int gpu_vendor)
{
    static const struct {
        unsigned   id;
        const char name[32];
    } vendors [] = {
        { GPU_MANUFACTURER_AMD,      "ATI"         },
        { GPU_MANUFACTURER_NVIDIA,   "NVIDIA"      },
        { GPU_MANUFACTURER_VIA,      "VIA"         },
        { GPU_MANUFACTURER_INTEL,    "Intel"       },
        { GPU_MANUFACTURER_S3,       "S3 Graphics" },
        { GPU_MANUFACTURER_QUALCOMM, "Qualcomm"    },
        { 0,                         "Unknown" }
    };

    int i = 0;
    for (i = 0; vendors[i].id != 0; i++) {
        if (vendors[i].id == gpu_vendor)
            break;
    }
    return vendors[i].name;
}