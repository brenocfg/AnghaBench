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
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  int /*<<< orphan*/  GpImage ;

/* Variables and functions */
 scalar_t__ InvalidParameter ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ load_wmf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static GpStatus decode_image_wmf(IStream *stream, GpImage **image)
{
    GpMetafile *metafile;
    GpStatus status;

    TRACE("%p %p\n", stream, image);

    if (!stream || !image)
        return InvalidParameter;

    status = load_wmf(stream, &metafile);
    if (status != Ok)
    {
        TRACE("Could not load metafile\n");
        return status;
    }

    *image = (GpImage *)metafile;
    TRACE("<-- %p\n", *image);

    return Ok;
}