#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* destroy ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ vlc_gl_t ;
struct vlc_gl_priv_t {int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_atomic_rc_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_objres_clear (int /*<<< orphan*/ ) ; 

void vlc_gl_Release(vlc_gl_t *gl)
{
    struct vlc_gl_priv_t *glpriv = (struct vlc_gl_priv_t *)gl;
    if (!vlc_atomic_rc_dec(&glpriv->rc))
        return;

    if (gl->destroy != NULL)
        gl->destroy(gl);
    vlc_objres_clear(VLC_OBJECT(gl));
    vlc_object_delete(gl);
}