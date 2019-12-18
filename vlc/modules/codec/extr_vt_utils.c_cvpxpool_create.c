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
struct TYPE_3__ {int i_chroma; unsigned int i_visible_width; unsigned int i_visible_height; } ;
typedef  TYPE_1__ video_format_t ;
typedef  scalar_t__ CVReturn ;
typedef  int /*<<< orphan*/ * CVPixelBufferRef ;
typedef  int /*<<< orphan*/ * CVPixelBufferPoolRef ;
typedef  int /*<<< orphan*/ * CFMutableDictionaryRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFDictionarySetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ CVPixelBufferPoolCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ CVPixelBufferPoolCreatePixelBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CVPixelBufferPoolRelease (int /*<<< orphan*/ *) ; 
#define  VLC_CODEC_CVPX_BGRA 132 
#define  VLC_CODEC_CVPX_I420 131 
#define  VLC_CODEC_CVPX_NV12 130 
#define  VLC_CODEC_CVPX_P010 129 
#define  VLC_CODEC_CVPX_UYVY 128 
 int /*<<< orphan*/ * cfdict_create (int) ; 
 int /*<<< orphan*/  cfdict_set_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kCVPixelBufferBytesPerRowAlignmentKey ; 
 int /*<<< orphan*/  kCVPixelBufferHeightKey ; 
 int /*<<< orphan*/  kCVPixelBufferIOSurfacePropertiesKey ; 
 int /*<<< orphan*/  kCVPixelBufferPixelFormatTypeKey ; 
 int /*<<< orphan*/  kCVPixelBufferPoolMaximumBufferAgeKey ; 
 int /*<<< orphan*/  kCVPixelBufferPoolMinimumBufferCountKey ; 
 int /*<<< orphan*/  kCVPixelBufferWidthKey ; 
 int kCVPixelFormatType_32BGRA ; 
 int kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange ; 
 int kCVPixelFormatType_420YpCbCr8Planar ; 
 int kCVPixelFormatType_422YpCbCr8 ; 
 scalar_t__ kCVReturnSuccess ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

CVPixelBufferPoolRef
cvpxpool_create(const video_format_t *fmt, unsigned count)
{
    int cvpx_format;
    switch (fmt->i_chroma)
    {
        case VLC_CODEC_CVPX_UYVY:
            cvpx_format = kCVPixelFormatType_422YpCbCr8;
            break;
        case VLC_CODEC_CVPX_NV12:
            cvpx_format = kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange;
            break;
        case VLC_CODEC_CVPX_I420:
            cvpx_format = kCVPixelFormatType_420YpCbCr8Planar;
            break;
        case VLC_CODEC_CVPX_BGRA:
            cvpx_format = kCVPixelFormatType_32BGRA;
            break;
        case VLC_CODEC_CVPX_P010:
            cvpx_format = 'x420'; /* kCVPixelFormatType_420YpCbCr10BiPlanarVideoRange */
            break;
        default:
            return NULL;
    }

    /* destination pixel buffer attributes */
    CFMutableDictionaryRef cvpx_attrs_dict = cfdict_create(5);
    if (unlikely(cvpx_attrs_dict == NULL))
        return NULL;
    CFMutableDictionaryRef pool_dict = cfdict_create(2);
    if (unlikely(pool_dict == NULL))
    {
        CFRelease(cvpx_attrs_dict);
        return NULL;
    }

    CFMutableDictionaryRef io_dict = cfdict_create(0);
    if (unlikely(io_dict == NULL))
    {
        CFRelease(cvpx_attrs_dict);
        CFRelease(pool_dict);
        return NULL;
    }
    CFDictionarySetValue(cvpx_attrs_dict,
                         kCVPixelBufferIOSurfacePropertiesKey, io_dict);
    CFRelease(io_dict);

    cfdict_set_int32(cvpx_attrs_dict, kCVPixelBufferPixelFormatTypeKey,
                     cvpx_format);
    cfdict_set_int32(cvpx_attrs_dict, kCVPixelBufferWidthKey, fmt->i_visible_width);
    cfdict_set_int32(cvpx_attrs_dict, kCVPixelBufferHeightKey, fmt->i_visible_height);
    /* Required by CIFilter to render IOSurface */
    cfdict_set_int32(cvpx_attrs_dict, kCVPixelBufferBytesPerRowAlignmentKey, 16);

    cfdict_set_int32(pool_dict, kCVPixelBufferPoolMinimumBufferCountKey, count);
    cfdict_set_int32(pool_dict, kCVPixelBufferPoolMaximumBufferAgeKey, 0);

    CVPixelBufferPoolRef pool;
    CVReturn err =
        CVPixelBufferPoolCreate(NULL, pool_dict, cvpx_attrs_dict, &pool);
    CFRelease(pool_dict);
    CFRelease(cvpx_attrs_dict);
    if (err != kCVReturnSuccess)
        return NULL;

    CVPixelBufferRef cvpxs[count];
    for (unsigned i = 0; i < count; ++i)
    {
        err = CVPixelBufferPoolCreatePixelBuffer(NULL, pool, &cvpxs[i]);
        if (err != kCVReturnSuccess)
        {
            CVPixelBufferPoolRelease(pool);
            pool = NULL;
            count = i;
            break;
        }
    }
    for (unsigned i = 0; i < count; ++i)
        CFRelease(cvpxs[i]);

    return pool;
}