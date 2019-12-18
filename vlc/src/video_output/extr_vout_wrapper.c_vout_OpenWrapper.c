#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_3__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
struct TYPE_22__ {int /*<<< orphan*/ * display_pool; int /*<<< orphan*/ * private_pool; int /*<<< orphan*/  original; } ;
typedef  TYPE_3__ vout_thread_sys_t ;
struct TYPE_20__ {scalar_t__ projection_mode; } ;
struct TYPE_23__ {TYPE_1__ fmt; int /*<<< orphan*/  source; } ;
typedef  TYPE_4__ vout_display_t ;
struct TYPE_24__ {TYPE_2__* sys; int /*<<< orphan*/  viewpoint_moved; } ;
typedef  TYPE_5__ vout_display_owner_t ;
typedef  int /*<<< orphan*/  vout_display_cfg_t ;
typedef  int /*<<< orphan*/  vlc_video_context ;
typedef  int /*<<< orphan*/  picture_pool_t ;

/* Variables and functions */
 unsigned int const DISPLAY_PICTURE_COUNT ; 
 int /*<<< orphan*/  Forward ; 
 scalar_t__ PROJECTION_MODE_RECTANGULAR ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int VLC_VAR_BOOL ; 
 int VLC_VAR_DOINHERIT ; 
 int /*<<< orphan*/  VOUT_MAX_PICTURES ; 
 int /*<<< orphan*/  VoutViewpointMoved ; 
 int /*<<< orphan*/  __MAX (int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*,unsigned int const,unsigned int const) ; 
 unsigned int const picture_pool_GetSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * picture_pool_NewFromFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_pool_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * picture_pool_Reserve (int /*<<< orphan*/ *,unsigned int const) ; 
 int /*<<< orphan*/  var_AddCallback (TYPE_2__*,char*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  var_Create (TYPE_2__*,char*,int) ; 
 char* var_InheritString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  var_SetBool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * vout_GetPool (TYPE_4__*,unsigned int const) ; 
 int /*<<< orphan*/  vout_IsDisplayFiltered (TYPE_4__*) ; 
 int /*<<< orphan*/  vout_display_Delete (TYPE_4__*) ; 
 TYPE_4__* vout_display_New (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,TYPE_5__*) ; 

vout_display_t *vout_OpenWrapper(vout_thread_t *vout,
                     const char *splitter_name, const vout_display_cfg_t *cfg,
                     vlc_video_context *vctx)
{
    vout_thread_sys_t *sys = vout->p;
    vout_display_t *vd;
    vout_display_owner_t owner = {
        .viewpoint_moved = VoutViewpointMoved, .sys = vout,
    };
    const char *modlist;
    char *modlistbuf = NULL;

    msg_Dbg(vout, "Opening vout display wrapper");

    if (splitter_name == NULL)
        modlist = modlistbuf = var_InheritString(vout, "vout");
    else
        modlist = "splitter,none";

    vd = vout_display_New(VLC_OBJECT(vout), &sys->original, vctx, cfg,
                          modlist, &owner);
    free(modlistbuf);

    if (vd == NULL)
        return NULL;

    sys->display_pool = NULL;

    const unsigned private_picture  = 4; /* XXX 3 for filter, 1 for SPU */
    const unsigned kept_picture     = 1; /* last displayed picture */
    const unsigned reserved_picture = DISPLAY_PICTURE_COUNT +
                                      private_picture +
                                      kept_picture;

    picture_pool_t *display_pool = vout_GetPool(vd, reserved_picture);
    if (display_pool == NULL)
        goto error;

#ifndef NDEBUG
    if ( picture_pool_GetSize(display_pool) < reserved_picture )
        msg_Warn(vout, "Not enough display buffers in the pool, requested %u got %u",
                 reserved_picture, picture_pool_GetSize(display_pool));
#endif

    if (!vout_IsDisplayFiltered(vd) &&
        picture_pool_GetSize(display_pool) >= reserved_picture) {
        sys->private_pool = picture_pool_Reserve(display_pool, private_picture);
    } else {
        sys->private_pool =
            picture_pool_NewFromFormat(&vd->source,
                                       __MAX(VOUT_MAX_PICTURES,
                                             reserved_picture - DISPLAY_PICTURE_COUNT));
    }
    if (sys->private_pool == NULL) {
        picture_pool_Release(display_pool);
        goto error;
    }
    sys->display_pool = display_pool;

#ifdef _WIN32
    var_Create(vout, "video-wallpaper", VLC_VAR_BOOL|VLC_VAR_DOINHERIT);
    var_AddCallback(vout, "video-wallpaper", Forward, vd);
#endif
    var_SetBool(VLC_OBJECT(vout), "viewpoint-changeable",
                vd->fmt.projection_mode != PROJECTION_MODE_RECTANGULAR);
    return vd;

error:
    vout_display_Delete(vd);
    return NULL;
}