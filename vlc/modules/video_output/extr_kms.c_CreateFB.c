#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_6__ {int width; int height; int drm_fourcc; int stride; int* offsets; size_t* handle; scalar_t__* map; int /*<<< orphan*/  drm_fd; scalar_t__* fb; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  size_t uint32_t ;
struct drm_mode_map_dumb {int width; int height; int bpp; size_t handle; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;
struct drm_mode_destroy_dumb {int width; int height; int bpp; size_t handle; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;
struct drm_mode_create_dumb {int width; int height; int bpp; size_t handle; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;
typedef  scalar_t__ deviceRval ;
typedef  int /*<<< orphan*/  destroy_req ;

/* Variables and functions */
 int ALIGN (int,unsigned int) ; 
 size_t ARRAY_SIZE (size_t*) ; 
#define  DRM_FORMAT_NV12 131 
#define  DRM_FORMAT_P010 130 
#define  DRM_FORMAT_P012 129 
#define  DRM_FORMAT_P016 128 
 int /*<<< orphan*/  DRM_IOCTL_MODE_CREATE_DUMB ; 
 int /*<<< orphan*/  DRM_IOCTL_MODE_DESTROY_DUMB ; 
 int /*<<< orphan*/  DRM_IOCTL_MODE_MAP_DUMB ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ drmIoctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_mode_map_dumb*) ; 
 scalar_t__ drmModeAddFB2 (int /*<<< orphan*/ ,int,int,int,size_t*,size_t*,size_t*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drmModeRmFB (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ drvFail ; 
 scalar_t__ drvSuccess ; 
 int /*<<< orphan*/  memset (struct drm_mode_map_dumb*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 

__attribute__((used)) static deviceRval CreateFB(vout_display_t *vd, const int buf)
{
    vout_display_sys_t *sys = vd->sys;
    struct drm_mode_create_dumb create_req = { .width = sys->width,
                                               .height = sys->height,
                                               .bpp = 32 };
    struct drm_mode_destroy_dumb destroy_req;
    struct drm_mode_map_dumb modify_req = {};
    unsigned int tile_width = 512, tile_height = 16;
    deviceRval ret;
    uint32_t i;
    uint32_t offsets[] = {0,0,0,0}, handles[] = {0,0,0,0},
            pitches[] = {0,0,0,0};

    switch(sys->drm_fourcc) {
#ifdef DRM_FORMAT_P010
    case DRM_FORMAT_P010:
#endif
#ifdef DRM_FORMAT_P012
    case DRM_FORMAT_P012:
#endif
#ifdef DRM_FORMAT_P016
    case DRM_FORMAT_P016:
#endif
#if defined(DRM_FORMAT_P010) || defined(DRM_FORMAT_P012) || defined(DRM_FORMAT_P016)
        sys->stride = ALIGN(sys->width*2, tile_width);
        sys->offsets[1] = sys->stride*ALIGN(sys->height, tile_height);
        create_req.height = 2*ALIGN(sys->height, tile_height);
        break;
#endif
    case DRM_FORMAT_NV12:
        sys->stride = ALIGN(sys->width, tile_width);
        sys->offsets[1] = sys->stride*ALIGN(sys->height, tile_height);
        create_req.height = 2*ALIGN(sys->height, tile_height);
        break;
    default:
        create_req.height = ALIGN(sys->height, tile_height);

        /*
         * width *4 so there's enough space for anything.
         */
        sys->stride = ALIGN(sys->width*4, tile_width);
        break;
    }

    ret = drmIoctl(sys->drm_fd, DRM_IOCTL_MODE_CREATE_DUMB, &create_req);
    if (ret < 0) {
        msg_Err(vd, "Cannot create dumb buffer");
        return drvFail;
    }

    sys->size = create_req.size;
    sys->handle[buf] = create_req.handle;

    /*
     * create framebuffer object for the dumb-buffer
     * index 0 has to be filled in any case.
     */
    for (i = 0; i < ARRAY_SIZE(handles) && (sys->offsets[i] || i < 1); i++) {
        handles[i] = create_req.handle;
        pitches[i] = sys->stride;
        offsets[i] = sys->offsets[i];
    }

    ret = drmModeAddFB2(sys->drm_fd, sys->width, sys->height, sys->drm_fourcc,
                        handles, pitches, offsets, &sys->fb[buf], 0);

    if (ret) {
        msg_Err(vd, "Cannot create frame buffer");
        ret = drvFail;
        goto err_destroy;
    }

    modify_req.handle = sys->handle[buf];
    ret = drmIoctl(sys->drm_fd, DRM_IOCTL_MODE_MAP_DUMB, &modify_req);
    if (ret) {
        msg_Err(vd, "Cannot map dumb buffer");
        ret = drvFail;
        goto err_fb;
    }

    sys->map[buf] = mmap(0, sys->size, PROT_READ | PROT_WRITE, MAP_SHARED,
                         sys->drm_fd, modify_req.offset);

    if (sys->map[buf] == MAP_FAILED) {
        msg_Err(vd, "Cannot mmap dumb buffer");
        ret = drvFail;
        goto err_fb;
    }
    return drvSuccess;

err_fb:
    drmModeRmFB(sys->drm_fd, sys->fb[buf]);
    sys->fb[buf] = 0;

err_destroy:
    memset(&destroy_req, 0, sizeof(destroy_req));
    destroy_req.handle = sys->handle[buf];
    drmIoctl(sys->drm_fd, DRM_IOCTL_MODE_DESTROY_DUMB, &destroy_req);
    return ret;
}