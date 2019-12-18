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
typedef  int /*<<< orphan*/  vout_window_t ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; } ;
typedef  TYPE_1__ vlc_decoder_device ;
struct vlc_decoder_device_priv {TYPE_1__ device; int /*<<< orphan*/  rc; } ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decoder_device_Open ; 
 int /*<<< orphan*/  free (char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_atomic_rc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_module_load (TYPE_1__*,char*,char*,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct vlc_decoder_device_priv* vlc_object_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

vlc_decoder_device *
vlc_decoder_device_Create(vout_window_t *window)
{
    struct vlc_decoder_device_priv *priv =
            vlc_object_create(window, sizeof (*priv));
    if (!priv)
        return NULL;
    char *name = var_InheritString(window, "dec-dev");
    module_t *module = vlc_module_load(&priv->device, "decoder device", name,
                                    true, decoder_device_Open, &priv->device,
                                    window);
    free(name);
    if (module == NULL)
    {
        vlc_object_delete(&priv->device);
        return NULL;
    }
    assert(priv->device.ops != NULL);
    vlc_atomic_rc_init(&priv->rc);
    return &priv->device;
}