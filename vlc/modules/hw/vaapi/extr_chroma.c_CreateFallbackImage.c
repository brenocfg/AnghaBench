#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
struct TYPE_10__ {TYPE_1__ format; } ;
typedef  TYPE_2__ picture_t ;
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_11__ {scalar_t__ fourcc; } ;
typedef  TYPE_3__ VAImageFormat ;
typedef  int /*<<< orphan*/  VAImage ;
typedef  int /*<<< orphan*/  VADisplay ;

/* Variables and functions */
 scalar_t__ VA_FOURCC_NV12 ; 
 scalar_t__ VA_FOURCC_P010 ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vaMaxNumImageFormats (int /*<<< orphan*/ ) ; 
 scalar_t__ vaQueryImageFormats (int /*<<< orphan*/ ,TYPE_3__*,int*) ; 
 TYPE_3__* vlc_alloc (int,int) ; 
 int /*<<< orphan*/  vlc_vaapi_CreateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int CreateFallbackImage(filter_t *filter, picture_t *src_pic,
                               VADisplay va_dpy, VAImage *image_fallback)
{
    int count = vaMaxNumImageFormats(va_dpy);

    VAImageFormat *fmts = vlc_alloc(count, sizeof (*fmts));
    if (unlikely(fmts == NULL))
        return VLC_ENOMEM;

    if (vaQueryImageFormats(va_dpy, fmts, &count))
    {
        free(fmts);
        return VLC_EGENERIC;
    }

    int i;
    for (i = 0; i < count; i++)
        if (fmts[i].fourcc == VA_FOURCC_NV12
         || fmts[i].fourcc == VA_FOURCC_P010)
            break;

    int ret;
    if ((fmts[i].fourcc == VA_FOURCC_NV12 || fmts[i].fourcc == VA_FOURCC_P010)
     && !vlc_vaapi_CreateImage(VLC_OBJECT(filter), va_dpy, &fmts[i],
                               src_pic->format.i_width, src_pic->format.i_height,
                               image_fallback))
        ret = VLC_SUCCESS;
    else
        ret = VLC_EGENERIC;

    free(fmts);

    return ret;
}