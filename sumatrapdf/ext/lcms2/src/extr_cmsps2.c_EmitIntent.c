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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
#define  INTENT_ABSOLUTE_COLORIMETRIC 131 
#define  INTENT_PERCEPTUAL 130 
#define  INTENT_RELATIVE_COLORIMETRIC 129 
#define  INTENT_SATURATION 128 
 int /*<<< orphan*/  _cmsIOPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static
void EmitIntent(cmsContext ContextID, cmsIOHANDLER* m, cmsUInt32Number RenderingIntent)
{
    const char *intent;

    switch (RenderingIntent) {

        case INTENT_PERCEPTUAL:            intent = "Perceptual"; break;
        case INTENT_RELATIVE_COLORIMETRIC: intent = "RelativeColorimetric"; break;
        case INTENT_ABSOLUTE_COLORIMETRIC: intent = "AbsoluteColorimetric"; break;
        case INTENT_SATURATION:            intent = "Saturation"; break;

        default: intent = "Undefined"; break;
    }

    _cmsIOPrintf(ContextID, m, "/RenderingIntent (%s)\n", intent );
}