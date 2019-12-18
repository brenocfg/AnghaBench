#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
typedef  scalar_t__ cmsUInt16Number ;
struct TYPE_6__ {int /*<<< orphan*/  (* Lerp16 ) (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,TYPE_2__*) ;} ;
struct TYPE_7__ {TYPE_1__ Interpolation; } ;
typedef  TYPE_2__ cmsInterpParams ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  BuildTable (int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMS_LERP_FLAGS_16BITS ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Fail (char*,int,scalar_t__,scalar_t__) ; 
 TYPE_2__* _cmsComputeInterpParams (int /*<<< orphan*/ ,int,int,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsFreeInterpParams (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,TYPE_2__*) ; 

__attribute__((used)) static
cmsInt32Number Check1D(cmsInt32Number nNodesToCheck, cmsBool  Down, cmsInt32Number max_err)
{
    cmsUInt32Number i;
    cmsUInt16Number in, out;
    cmsInterpParams* p;
    cmsUInt16Number* Tab;

    Tab = (cmsUInt16Number*) malloc(sizeof(cmsUInt16Number)* nNodesToCheck);
    if (Tab == NULL) return 0;

    p = _cmsComputeInterpParams(DbgThread(), nNodesToCheck, 1, 1, Tab, CMS_LERP_FLAGS_16BITS);
    if (p == NULL) return 0;

    BuildTable(nNodesToCheck, Tab, Down);

    for (i=0; i <= 0xffff; i++) {

        in = (cmsUInt16Number) i;
        out = 0;

        p ->Interpolation.Lerp16(DbgThread(), &in, &out, p);

        if (Down) out = 0xffff - out;

        if (abs(out - in) > max_err) {

            Fail("(%dp): Must be %x, But is %x : ", nNodesToCheck, in, out);
            _cmsFreeInterpParams(DbgThread(), p);
            free(Tab);
            return 0;
        }
    }

    _cmsFreeInterpParams(DbgThread(), p);
    free(Tab);
    return 1;
}