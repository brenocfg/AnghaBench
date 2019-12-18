#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cmsUInt16Number ;
typedef  int cmsInt32Number ;
typedef  scalar_t__ cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_2__ {int /*<<< orphan*/  hIlimit; int /*<<< orphan*/  hLab2sRGB; } ;
typedef  TYPE_1__ FakeCMYKParams ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__*,int) ; 
 scalar_t__ cmsmin (scalar_t__,scalar_t__) ; 

__attribute__((used)) static
cmsInt32Number ForwardSampler(cmsContext ContextID, register const cmsUInt16Number In[], cmsUInt16Number Out[], void* Cargo)
{
    FakeCMYKParams* p = (FakeCMYKParams*) Cargo;
    cmsFloat64Number rgb[3], cmyk[4];
    cmsFloat64Number c, m, y, k;

    cmsDoTransform(DbgThread(), p ->hLab2sRGB, In, rgb, 1);

    c = 1 - rgb[0];
    m = 1 - rgb[1];
    y = 1 - rgb[2];

    k = (c < m ? cmsmin(c, y) : cmsmin(m, y));

    // NONSENSE WARNING!: I'm doing this just because this is a test
    // profile that may have ink limit up to 400%. There is no UCR here
    // so the profile is basically useless for anything but testing.

    cmyk[0] = c;
    cmyk[1] = m;
    cmyk[2] = y;
    cmyk[3] = k;

    cmsDoTransform(DbgThread(), p ->hIlimit, cmyk, Out, 1);

    return 1;
}