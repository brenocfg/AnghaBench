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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  pf_remove; int /*<<< orphan*/  pf_find; int /*<<< orphan*/  pf_store; int /*<<< orphan*/ * p_module; } ;
typedef  TYPE_1__ vlc_keystore ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * module_need (TYPE_1__*,char*,char const*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

__attribute__((used)) static vlc_keystore *
keystore_create(vlc_object_t *p_parent, const char *psz_name)
{
    vlc_keystore *p_keystore = vlc_custom_create(p_parent, sizeof (*p_keystore),
                                                 "keystore");
    if (unlikely(p_keystore == NULL))
        return NULL;

    p_keystore->p_module = module_need(p_keystore, "keystore", psz_name, true);
    if (p_keystore->p_module == NULL)
    {
        vlc_object_delete(p_keystore);
        return NULL;
    }
    assert(p_keystore->pf_store);
    assert(p_keystore->pf_find);
    assert(p_keystore->pf_remove);

    return p_keystore;
}