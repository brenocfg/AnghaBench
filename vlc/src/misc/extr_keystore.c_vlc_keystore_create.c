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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_keystore ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * keystore_create (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 

vlc_keystore *
vlc_keystore_create(vlc_object_t *p_parent)
{
    assert(p_parent);

    char *modlist = var_InheritString(p_parent, "keystore");
    vlc_keystore *p_keystore = keystore_create(p_parent, modlist);

    free(modlist);
    return p_keystore;
}