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
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_10__ {int /*<<< orphan*/  cache; int /*<<< orphan*/  dest_pics; int /*<<< orphan*/  dpy; } ;
typedef  TYPE_2__ filter_sys_t ;
struct TYPE_11__ {int /*<<< orphan*/  image_id; int /*<<< orphan*/  buf; } ;
typedef  TYPE_3__ VAImage ;
typedef  int /*<<< orphan*/  VADisplay ;

/* Variables and functions */
 int /*<<< orphan*/  FillVAImageFromPicture (TYPE_3__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  picture_CopyProperties (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * picture_pool_Wait (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_vaapi_DeriveImage (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ vlc_vaapi_DestroyImage (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_vaapi_MapBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  vlc_vaapi_PicAttachContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vaapi_PicGetSurface (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_vaapi_UnmapBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static picture_t *
UploadSurface(filter_t *filter, picture_t *src)
{
    filter_sys_t   *p_sys = filter->p_sys;
    VADisplay const va_dpy = p_sys->dpy;
    VAImage         dest_img;
    void *          dest_buf;
    picture_t *     dest_pic = picture_pool_Wait(p_sys->dest_pics);

    if (!dest_pic)
    {
        msg_Err(filter, "cannot retrieve picture from the dest pics pool");
        goto ret;
    }
    vlc_vaapi_PicAttachContext(dest_pic);
    picture_CopyProperties(dest_pic, src);

    if (vlc_vaapi_DeriveImage(VLC_OBJECT(filter), va_dpy,
                              vlc_vaapi_PicGetSurface(dest_pic), &dest_img)
        || vlc_vaapi_MapBuffer(VLC_OBJECT(filter), va_dpy,
                               dest_img.buf, &dest_buf))
        goto error;

    FillVAImageFromPicture(&dest_img, dest_buf, dest_pic,
                           src, &p_sys->cache);

    if (vlc_vaapi_UnmapBuffer(VLC_OBJECT(filter), va_dpy, dest_img.buf)
        || vlc_vaapi_DestroyImage(VLC_OBJECT(filter),
                                  va_dpy, dest_img.image_id))
        goto error;

ret:
    picture_Release(src);
    return dest_pic;

error:
    picture_Release(dest_pic);
    dest_pic = NULL;
    goto ret;
}