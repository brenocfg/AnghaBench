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
typedef  int /*<<< orphan*/  vlc_gl_t ;
struct vlc_gl_priv_t {int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_atomic_rc_inc (int /*<<< orphan*/ *) ; 

void vlc_gl_Hold(vlc_gl_t *gl)
{
    struct vlc_gl_priv_t *glpriv = (struct vlc_gl_priv_t *)gl;
    vlc_atomic_rc_inc(&glpriv->rc);
}