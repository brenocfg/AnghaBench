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
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ cmsCIEXYZ ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsIOPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  _cmsReadMediaWhitePoint (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void EmitPQRStage(cmsContext ContextID, cmsIOHANDLER* m, cmsHPROFILE hProfile, int DoBPC, int lIsAbsolute)
{


        if (lIsAbsolute) {

            // For absolute colorimetric intent, encode back to relative
            // and generate a relative Pipeline

            // Relative encoding is obtained across XYZpcs*(D50/WhitePoint)

            cmsCIEXYZ White;

            _cmsReadMediaWhitePoint(ContextID, &White, hProfile);

            _cmsIOPrintf(ContextID, m,"/MatrixPQR [1 0 0 0 1 0 0 0 1 ]\n");
            _cmsIOPrintf(ContextID, m,"/RangePQR [ -0.5 2 -0.5 2 -0.5 2 ]\n");

            _cmsIOPrintf(ContextID, m, "%% Absolute colorimetric -- encode to relative to maximize LUT usage\n"
                      "/TransformPQR [\n"
                      "{0.9642 mul %g div exch pop exch pop exch pop exch pop} bind\n"
                      "{1.0000 mul %g div exch pop exch pop exch pop exch pop} bind\n"
                      "{0.8249 mul %g div exch pop exch pop exch pop exch pop} bind\n]\n",
                      White.X, White.Y, White.Z);
            return;
        }


        _cmsIOPrintf(ContextID, m,"%% Bradford Cone Space\n"
                 "/MatrixPQR [0.8951 -0.7502 0.0389 0.2664 1.7135 -0.0685 -0.1614 0.0367 1.0296 ] \n");

        _cmsIOPrintf(ContextID, m, "/RangePQR [ -0.5 2 -0.5 2 -0.5 2 ]\n");


        // No BPC

        if (!DoBPC) {

            _cmsIOPrintf(ContextID, m, "%% VonKries-like transform in Bradford Cone Space\n"
                      "/TransformPQR [\n"
                      "{exch pop exch 3 get mul exch pop exch 3 get div} bind\n"
                      "{exch pop exch 4 get mul exch pop exch 4 get div} bind\n"
                      "{exch pop exch 5 get mul exch pop exch 5 get div} bind\n]\n");
        } else {

            // BPC

            _cmsIOPrintf(ContextID, m, "%% VonKries-like transform in Bradford Cone Space plus BPC\n"
                      "/TransformPQR [\n");

            _cmsIOPrintf(ContextID, m, "{4 index 3 get div 2 index 3 get mul "
                    "2 index 3 get 2 index 3 get sub mul "
                    "2 index 3 get 4 index 3 get 3 index 3 get sub mul sub "
                    "3 index 3 get 3 index 3 get exch sub div "
                    "exch pop exch pop exch pop exch pop } bind\n");

            _cmsIOPrintf(ContextID, m, "{4 index 4 get div 2 index 4 get mul "
                    "2 index 4 get 2 index 4 get sub mul "
                    "2 index 4 get 4 index 4 get 3 index 4 get sub mul sub "
                    "3 index 4 get 3 index 4 get exch sub div "
                    "exch pop exch pop exch pop exch pop } bind\n");

            _cmsIOPrintf(ContextID, m, "{4 index 5 get div 2 index 5 get mul "
                    "2 index 5 get 2 index 5 get sub mul "
                    "2 index 5 get 4 index 5 get 3 index 5 get sub mul sub "
                    "3 index 5 get 3 index 5 get exch sub div "
                    "exch pop exch pop exch pop exch pop } bind\n]\n");

        }


}