#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _cmstransform_struct {int /*<<< orphan*/  (* OldXform ) (int /*<<< orphan*/ ,struct _cmstransform_struct*,void*,void*,scalar_t__,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  scalar_t__ cmsUInt32Number ;
struct TYPE_4__ {scalar_t__ BytesPerLineIn; scalar_t__ BytesPerLineOut; int /*<<< orphan*/  BytesPerPlaneIn; } ;
typedef  TYPE_1__ cmsStride ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsHandleExtraChannels (int /*<<< orphan*/ ,struct _cmstransform_struct*,void const*,void*,scalar_t__,scalar_t__,TYPE_1__ const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct _cmstransform_struct*,void*,void*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void _cmsTransform2toTransformAdaptor(cmsContext ContextID, struct _cmstransform_struct *CMMcargo,
                                      const void* InputBuffer,
                                      void* OutputBuffer,
                                      cmsUInt32Number PixelsPerLine,
                                      cmsUInt32Number LineCount,
                                      const cmsStride* Stride)
{

       cmsUInt32Number i, strideIn, strideOut;

       _cmsHandleExtraChannels(ContextID, CMMcargo, InputBuffer, OutputBuffer, PixelsPerLine, LineCount, Stride);

       strideIn = 0;
       strideOut = 0;

       for (i = 0; i < LineCount; i++) {

              void *accum = (cmsUInt8Number*)InputBuffer + strideIn;
              void *output = (cmsUInt8Number*)OutputBuffer + strideOut;

              CMMcargo->OldXform(ContextID, CMMcargo, accum, output, PixelsPerLine, Stride->BytesPerPlaneIn);

              strideIn += Stride->BytesPerLineIn;
              strideOut += Stride->BytesPerLineOut;
       }
}