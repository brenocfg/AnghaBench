#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
struct TYPE_35__ {TYPE_8__* sys; } ;
typedef  TYPE_7__ vout_display_t ;
struct TYPE_31__ {scalar_t__ y; scalar_t__ x; scalar_t__ height; scalar_t__ width; } ;
struct TYPE_32__ {TYPE_3__ place; } ;
struct TYPE_34__ {int /*<<< orphan*/  dev; } ;
struct TYPE_36__ {size_t d3dregion_count; scalar_t__ d3dregion_format; TYPE_4__ area; TYPE_6__ d3d_dev; TYPE_11__* d3dregion; } ;
typedef  TYPE_8__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_37__ {float i_original_picture_width; float i_original_picture_height; int i_alpha; TYPE_10__* p_region; } ;
typedef  TYPE_9__ subpicture_t ;
struct TYPE_33__ {scalar_t__ i_width; scalar_t__ i_height; float const i_visible_width; float const i_visible_height; float const i_x_offset; float const i_y_offset; } ;
struct TYPE_25__ {float const i_x; float const i_y; int i_alpha; TYPE_5__ fmt; TYPE_2__* p_picture; struct TYPE_25__* p_next; } ;
typedef  TYPE_10__ subpicture_region_t ;
struct TYPE_26__ {scalar_t__ format; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  vertex; int /*<<< orphan*/ * texture; } ;
typedef  TYPE_11__ d3d_region_t ;
struct TYPE_30__ {TYPE_1__* p; } ;
struct TYPE_29__ {int i_pitch; int /*<<< orphan*/ * p_pixels; } ;
struct TYPE_28__ {int Pitch; int /*<<< orphan*/ * pBits; } ;
struct TYPE_27__ {float left; float right; float top; float bottom; } ;
typedef  TYPE_12__ RECT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_13__ D3DLOCKED_RECT ;

/* Variables and functions */
 scalar_t__ D3DFMT_A8B8G8R8 ; 
 int /*<<< orphan*/  D3DPOOL_DEFAULT ; 
 int /*<<< orphan*/  D3DUSAGE_DYNAMIC ; 
 int /*<<< orphan*/  Direct3D9SetupVertices (int /*<<< orphan*/ ,TYPE_12__*,TYPE_12__*,TYPE_12__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DDevice9_CreateTexture (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirect3DTexture9_LockRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DTexture9_UnlockRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ORIENT_NORMAL ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int __MIN (int,int) ; 
 TYPE_11__* calloc (size_t,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_7__*,char*,float,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_7__*,char*,...) ; 

__attribute__((used)) static void Direct3D9ImportSubpicture(vout_display_t *vd,
                                     size_t *count_ptr, d3d_region_t **region,
                                     subpicture_t *subpicture)
{
    vout_display_sys_t *sys = vd->sys;

    size_t count = 0;
    for (subpicture_region_t *r = subpicture->p_region; r; r = r->p_next)
        count++;

    *count_ptr = count;
    *region    = calloc(count, sizeof(**region));
    if (*region == NULL) {
        *count_ptr = 0;
        return;
    }

    int i = 0;
    for (subpicture_region_t *r = subpicture->p_region; r; r = r->p_next, i++) {
        d3d_region_t *d3dr = &(*region)[i];
        HRESULT hr;

        d3dr->texture = NULL;
        for (size_t j = 0; j < sys->d3dregion_count; j++) {
            d3d_region_t *cache = &sys->d3dregion[j];
            if (cache->texture &&
                cache->format == sys->d3dregion_format &&
                cache->width  == r->fmt.i_width &&
                cache->height == r->fmt.i_height) {
                *d3dr = *cache;
                memset(cache, 0, sizeof(*cache));
                break;
            }
        }
        if (!d3dr->texture) {
            d3dr->format = sys->d3dregion_format;
            d3dr->width  = r->fmt.i_width;
            d3dr->height = r->fmt.i_height;
            hr = IDirect3DDevice9_CreateTexture(sys->d3d_dev.dev,
                                                d3dr->width, d3dr->height,
                                                1,
                                                D3DUSAGE_DYNAMIC,
                                                d3dr->format,
                                                D3DPOOL_DEFAULT,
                                                &d3dr->texture,
                                                NULL);
            if (FAILED(hr)) {
                d3dr->texture = NULL;
                msg_Err(vd, "Failed to create %dx%d texture for OSD (hr=0x%lX)",
                        d3dr->width, d3dr->height, hr);
                continue;
            }
#ifndef NDEBUG
            msg_Dbg(vd, "Created %dx%d texture for OSD",
                    r->fmt.i_width, r->fmt.i_height);
#endif
        }

        D3DLOCKED_RECT lock;
        hr = IDirect3DTexture9_LockRect(d3dr->texture, 0, &lock, NULL, 0);
        if (SUCCEEDED(hr)) {
            uint8_t  *dst_data   = lock.pBits;
            int       dst_pitch  = lock.Pitch;
            uint8_t  *src_data   = r->p_picture->p->p_pixels;
            int       src_pitch  = r->p_picture->p->i_pitch;

            if (d3dr->format == D3DFMT_A8B8G8R8) {
                if (dst_pitch == r->p_picture->p->i_pitch) {
                    memcpy(dst_data, src_data, r->fmt.i_height * dst_pitch);
                } else {
                    int copy_pitch = __MIN(dst_pitch, r->p_picture->p->i_pitch);
                    for (unsigned y = 0; y < r->fmt.i_height; y++) {
                        memcpy(&dst_data[y * dst_pitch], &src_data[y * src_pitch], copy_pitch);
                    }
                }
            } else {
                int copy_pitch = __MIN(dst_pitch, r->p_picture->p->i_pitch);
                for (unsigned y = 0; y < r->fmt.i_height; y++) {
                    for (int x = 0; x < copy_pitch; x += 4) {
                        dst_data[y * dst_pitch + x + 0] = src_data[y * src_pitch + x + 2];
                        dst_data[y * dst_pitch + x + 1] = src_data[y * src_pitch + x + 1];
                        dst_data[y * dst_pitch + x + 2] = src_data[y * src_pitch + x + 0];
                        dst_data[y * dst_pitch + x + 3] = src_data[y * src_pitch + x + 3];
                    }
                }
            }
            hr = IDirect3DTexture9_UnlockRect(d3dr->texture, 0);
            if (FAILED(hr))
                msg_Err(vd, "Failed to unlock the texture");
        } else {
            msg_Err(vd, "Failed to lock the texture");
        }

        /* Map the subpicture to sys->sys.sys.place */
        const float scale_w = (float)(sys->area.place.width)  / subpicture->i_original_picture_width;
        const float scale_h = (float)(sys->area.place.height) / subpicture->i_original_picture_height;

        RECT rect_in_display;
        rect_in_display.left   =            scale_w * r->i_x,
        rect_in_display.right  = rect_in_display.left + scale_w * r->fmt.i_visible_width,
        rect_in_display.top    =            scale_h * r->i_y,
        rect_in_display.bottom = rect_in_display.top  + scale_h * r->fmt.i_visible_height;

        rect_in_display.left   += sys->area.place.x;
        rect_in_display.right  += sys->area.place.x;
        rect_in_display.top    += sys->area.place.y;
        rect_in_display.bottom += sys->area.place.y;

        RECT texture_rect;
        texture_rect.left   = 0;
        texture_rect.right  = r->fmt.i_width;
        texture_rect.top    = 0;
        texture_rect.bottom = r->fmt.i_height;

        RECT texture_visible_rect;
        texture_visible_rect.left   = r->fmt.i_x_offset;
        texture_visible_rect.right  = r->fmt.i_x_offset + r->fmt.i_visible_width;
        texture_visible_rect.top    = r->fmt.i_y_offset;
        texture_visible_rect.bottom = r->fmt.i_y_offset + r->fmt.i_visible_height;

        Direct3D9SetupVertices(d3dr->vertex, &texture_rect, &texture_visible_rect,
                              &rect_in_display, subpicture->i_alpha * r->i_alpha / 255, ORIENT_NORMAL);
    }
}