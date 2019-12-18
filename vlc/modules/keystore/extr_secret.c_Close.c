#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_2__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ vlc_keystore ;
typedef  int /*<<< orphan*/  SecretService ;

/* Variables and functions */
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secret_service_disconnect () ; 

__attribute__((used)) static void
Close(vlc_object_t *p_this)
{
    vlc_keystore *p_keystore = (vlc_keystore *)p_this;
    SecretService *p_ss = (SecretService *) p_keystore->p_sys;
    g_object_unref(p_ss);
    secret_service_disconnect();
}