#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ (* p_glGetError ) () ;int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glDeleteTextures ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glGetTexImage ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* p_glBindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glEnd ) () ;int /*<<< orphan*/  (* p_glVertex2f ) (float,float) ;int /*<<< orphan*/  (* p_glTexCoord2f ) (double,double) ;int /*<<< orphan*/  (* p_glBegin ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glClear ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glClearColor ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glLoadIdentity ) () ;int /*<<< orphan*/  (* p_glMatrixMode ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glViewport ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* p_glDrawBuffer ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glEnable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexImage2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*) ;int /*<<< orphan*/  (* p_glGenTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_2__ gl; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* glDeleteFramebuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* glBindFramebuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glFramebufferTexture2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glGenFramebuffers ) (int,int /*<<< orphan*/ *) ;} ;
struct wined3d_gl_info {TYPE_3__ gl_ops; TYPE_1__ fbo_ops; } ;
typedef  int /*<<< orphan*/  readback ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_BGRA ; 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_LIGHTING ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_RGBA8 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_R ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int /*<<< orphan*/  GL_TRIANGLE_STRIP ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT_8_8_8_8 ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT_8_8_8_8_REV ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ color_match (int,int,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub10 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub17 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub18 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub19 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub20 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub21 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub22 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub23 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub25 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub26 () ; 
 int /*<<< orphan*/  stub27 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub28 () ; 
 int /*<<< orphan*/  stub29 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub30 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub31 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub32 (double,double) ; 
 int /*<<< orphan*/  stub33 (float,float) ; 
 int /*<<< orphan*/  stub34 (double,double) ; 
 int /*<<< orphan*/  stub35 (float,float) ; 
 int /*<<< orphan*/  stub36 (double,double) ; 
 int /*<<< orphan*/  stub37 (float,float) ; 
 int /*<<< orphan*/  stub38 (double,double) ; 
 int /*<<< orphan*/  stub39 (float,float) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub40 () ; 
 int /*<<< orphan*/  stub41 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub42 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub43 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub44 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub45 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub46 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub47 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub48 () ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL check_filter(const struct wined3d_gl_info *gl_info, GLenum internal)
{
    static const DWORD data[] = {0x00000000, 0xffffffff};
    GLuint tex, fbo, buffer;
    DWORD readback[16 * 1];
    BOOL ret = FALSE;

    /* Render a filtered texture and see what happens. This is intended to detect the lack of
     * float16 filtering on ATI X1000 class cards. The drivers disable filtering instead of
     * falling back to software. If this changes in the future this code will get fooled and
     * apps might hit the software path due to incorrectly advertised caps.
     *
     * Its unlikely that this changes however. GL Games like Mass Effect depend on the filter
     * disable fallback, if Apple or ATI ever change the driver behavior they will break more
     * than Wine. The Linux binary <= r500 driver is not maintained any more anyway
     */

    while (gl_info->gl_ops.gl.p_glGetError());

    gl_info->gl_ops.gl.p_glGenTextures(1, &buffer);
    gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D, buffer);
    memset(readback, 0x7e, sizeof(readback));
    gl_info->gl_ops.gl.p_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 16, 1, 0,
            GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, readback);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    gl_info->gl_ops.gl.p_glGenTextures(1, &tex);
    gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D, tex);
    gl_info->gl_ops.gl.p_glTexImage2D(GL_TEXTURE_2D, 0, internal, 2, 1, 0,
            GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, data);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    gl_info->gl_ops.gl.p_glEnable(GL_TEXTURE_2D);

    gl_info->fbo_ops.glGenFramebuffers(1, &fbo);
    gl_info->fbo_ops.glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    gl_info->fbo_ops.glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer, 0);
    gl_info->gl_ops.gl.p_glDrawBuffer(GL_COLOR_ATTACHMENT0);

    gl_info->gl_ops.gl.p_glViewport(0, 0, 16, 1);
    gl_info->gl_ops.gl.p_glDisable(GL_LIGHTING);
    gl_info->gl_ops.gl.p_glMatrixMode(GL_MODELVIEW);
    gl_info->gl_ops.gl.p_glLoadIdentity();
    gl_info->gl_ops.gl.p_glMatrixMode(GL_PROJECTION);
    gl_info->gl_ops.gl.p_glLoadIdentity();

    gl_info->gl_ops.gl.p_glClearColor(0, 1, 0, 0);
    gl_info->gl_ops.gl.p_glClear(GL_COLOR_BUFFER_BIT);

    gl_info->gl_ops.gl.p_glBegin(GL_TRIANGLE_STRIP);
    gl_info->gl_ops.gl.p_glTexCoord2f(0.0, 0.0);
    gl_info->gl_ops.gl.p_glVertex2f(-1.0f, -1.0f);
    gl_info->gl_ops.gl.p_glTexCoord2f(1.0, 0.0);
    gl_info->gl_ops.gl.p_glVertex2f(1.0f, -1.0f);
    gl_info->gl_ops.gl.p_glTexCoord2f(0.0, 1.0);
    gl_info->gl_ops.gl.p_glVertex2f(-1.0f, 1.0f);
    gl_info->gl_ops.gl.p_glTexCoord2f(1.0, 1.0);
    gl_info->gl_ops.gl.p_glVertex2f(1.0f, 1.0f);
    gl_info->gl_ops.gl.p_glEnd();

    gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D, buffer);
    memset(readback, 0x7f, sizeof(readback));
    gl_info->gl_ops.gl.p_glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, readback);
    if (color_match(readback[6], 0xffffffff, 5) || color_match(readback[6], 0x00000000, 5)
            || color_match(readback[9], 0xffffffff, 5) || color_match(readback[9], 0x00000000, 5))
    {
        TRACE("Read back colors 0x%08x and 0x%08x close to unfiltered color, assuming no filtering\n",
              readback[6], readback[9]);
        ret = FALSE;
    }
    else
    {
        TRACE("Read back colors are 0x%08x and 0x%08x, assuming texture is filtered\n",
              readback[6], readback[9]);
        ret = TRUE;
    }

    gl_info->fbo_ops.glBindFramebuffer(GL_FRAMEBUFFER, 0);
    gl_info->fbo_ops.glDeleteFramebuffers(1, &fbo);
    gl_info->gl_ops.gl.p_glDeleteTextures(1, &tex);
    gl_info->gl_ops.gl.p_glDeleteTextures(1, &buffer);
    gl_info->gl_ops.gl.p_glDisable(GL_TEXTURE_2D);

    if (gl_info->gl_ops.gl.p_glGetError())
    {
        FIXME("Error during filtering test for format %x, returning no filtering\n", internal);
        ret = FALSE;
    }

    return ret;
}