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
struct _cmstransform_struct {int dummy; } ;
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 double floor (int) ; 

cmsUInt8Number* my_Unroll565(cmsContext ContextID, register struct _cmstransform_struct* nfo,
                            register cmsUInt16Number wIn[],
                            register cmsUInt8Number* accum,
                            register cmsUInt32Number Stride)
{
    cmsUInt16Number pixel = *(cmsUInt16Number*) accum;  // Take whole pixel

    double r = floor(((double) (pixel & 31) * 65535.0) / 31.0 + 0.5);
    double g = floor((((pixel >> 5) & 63) * 65535.0) / 63.0 + 0.5);
    double b = floor((((pixel >> 11) & 31) * 65535.0) / 31.0 + 0.5);

    wIn[2] = (cmsUInt16Number) r;
    wIn[1] = (cmsUInt16Number) g;
    wIn[0] = (cmsUInt16Number) b;

    return accum + 2;
}