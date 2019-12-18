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
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  _cmsTRANSFORM ;

/* Variables and functions */
 scalar_t__ floor (int) ; 

cmsUInt8Number* my_Pack565(cmsContext ContextID, register _cmsTRANSFORM* info,
                           register cmsUInt16Number wOut[],
                           register cmsUInt8Number* output,
                           register cmsUInt32Number Stride)
{

    register cmsUInt16Number pixel;
    int r, g, b;

    r = (int) floor(( wOut[2] * 31) / 65535.0 + 0.5);
    g = (int) floor(( wOut[1] * 63) / 65535.0 + 0.5);
    b = (int) floor(( wOut[0] * 31) / 65535.0 + 0.5);


    pixel = (r & 31)  | (( g & 63) << 5) | ((b & 31) << 11);


    *(cmsUInt16Number*) output = pixel;
    return output + 2;
}