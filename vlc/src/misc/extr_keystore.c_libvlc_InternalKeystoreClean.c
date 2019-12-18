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
struct TYPE_3__ {int /*<<< orphan*/ * p_memory_keystore; } ;
typedef  TYPE_1__ libvlc_priv_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* libvlc_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_keystore_release (int /*<<< orphan*/ *) ; 

void
libvlc_InternalKeystoreClean(libvlc_int_t *p_libvlc)
{
    assert(p_libvlc != NULL);
    libvlc_priv_t *p_priv = libvlc_priv(p_libvlc);

    if (p_priv->p_memory_keystore != NULL)
    {
        vlc_keystore_release(p_priv->p_memory_keystore);
        p_priv->p_memory_keystore = NULL;
    }
}