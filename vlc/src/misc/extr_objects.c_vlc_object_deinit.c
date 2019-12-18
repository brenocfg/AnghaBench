#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  var_lock; int /*<<< orphan*/  var_wait; int /*<<< orphan*/ * resources; } ;
typedef  TYPE_1__ vlc_object_internals_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  var_DestroyAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* vlc_internals (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

void vlc_object_deinit(vlc_object_t *obj)
{
    vlc_object_internals_t *priv = vlc_internals(obj);

    assert(priv->resources == NULL);

    /* Destroy the associated variables. */
    int canc = vlc_savecancel();
    var_DestroyAll(obj);
    vlc_restorecancel(canc);

    vlc_cond_destroy(&priv->var_wait);
    vlc_mutex_destroy(&priv->var_lock);
    free(priv);
}