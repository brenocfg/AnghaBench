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
typedef  scalar_t__ CVReturn ;
typedef  int /*<<< orphan*/ * CVPixelBufferRef ;
typedef  int /*<<< orphan*/  CVPixelBufferPoolRef ;

/* Variables and functions */
 scalar_t__ CVPixelBufferPoolCreatePixelBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ kCVReturnSuccess ; 

CVPixelBufferRef
cvpxpool_new_cvpx(CVPixelBufferPoolRef pool)
{
    CVPixelBufferRef cvpx;
    CVReturn err = CVPixelBufferPoolCreatePixelBuffer(NULL, pool, &cvpx);

    if (err != kCVReturnSuccess)
        return NULL;

    return cvpx;
}