#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  cfg; TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_10__ {TYPE_1__* anw; TYPE_4__* p_window; int /*<<< orphan*/  embed; } ;
typedef  TYPE_3__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  vlc_gl_t ;
typedef  int uint16_t ;
struct TYPE_11__ {int /*<<< orphan*/  p_surface; scalar_t__ b_opaque; } ;
typedef  TYPE_4__ android_window ;
struct TYPE_12__ {int* bits; } ;
struct TYPE_8__ {scalar_t__ (* setBuffersGeometry ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;scalar_t__ (* winLock ) (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* unlockAndPost ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ ANativeWindow_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  VLC_OPENGL_ES2 ; 
 int /*<<< orphan*/  WINDOW_FORMAT_RGB_565 ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 char* var_InheritString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * vlc_gl_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vlc_gl_MakeCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_gl_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_gl_ReleaseCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_gl_Resize (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vlc_gl_Swap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ClearSurface(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;

    if (sys->p_window->b_opaque)
    {
        /* Clear the surface to black with OpenGL ES 2 */
        char *modlist = var_InheritString(sys->embed, "gles2");
        vlc_gl_t *gl = vlc_gl_Create(vd->cfg, VLC_OPENGL_ES2, modlist);
        free(modlist);
        if (gl == NULL)
            return;

        if (vlc_gl_MakeCurrent(gl))
            goto end;

        vlc_gl_Resize(gl, 1, 1);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        vlc_gl_Swap(gl);

        vlc_gl_ReleaseCurrent(gl);

end:
        vlc_gl_Release(gl);
    }
    else
    {
        android_window *p_window = sys->p_window;
        ANativeWindow_Buffer buf;

        if (sys->anw->setBuffersGeometry(p_window->p_surface, 1, 1,
                                         WINDOW_FORMAT_RGB_565) == 0
          && sys->anw->winLock(p_window->p_surface, &buf, NULL) == 0)
        {
            uint16_t *p_bit = buf.bits;
            p_bit[0] = 0x0000;
            sys->anw->unlockAndPost(p_window->p_surface);
        }
    }
}