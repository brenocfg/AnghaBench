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
typedef  int /*<<< orphan*/  OPJ_TRANSFORM ;

/* Variables and functions */
 int /*<<< orphan*/  TRF_2D_DWT ; 
 int /*<<< orphan*/  TRF_3D_DWT ; 
 int /*<<< orphan*/  TRF_UNKNOWN ; 
 scalar_t__ strncmp (char*,char*,int) ; 

OPJ_TRANSFORM give_transform(char transform[4])
{
    if (strncmp(transform, "2DWT", 4) == 0) {
        return TRF_2D_DWT;
    }
    if (strncmp(transform, "3DWT", 4) == 0) {
        return TRF_3D_DWT;
    }
    return TRF_UNKNOWN;
}