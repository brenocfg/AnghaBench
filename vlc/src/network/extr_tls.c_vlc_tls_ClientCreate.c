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
typedef  int /*<<< orphan*/  vlc_tls_client_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tls_client_load ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * vlc_module_load (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ *) ; 

vlc_tls_client_t *vlc_tls_ClientCreate(vlc_object_t *obj)
{
    vlc_tls_client_t *crd = vlc_custom_create(obj, sizeof (*crd),
                                              "tls client");
    if (unlikely(crd == NULL))
        return NULL;

    if (vlc_module_load(crd, "tls client", NULL, false,
                        tls_client_load, crd) == NULL)
    {
        msg_Err (crd, "TLS client plugin not available");
        vlc_object_delete(crd);
        return NULL;
    }

    return crd;
}