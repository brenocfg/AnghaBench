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
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_libvlc_int; } ;
typedef  TYPE_1__ libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char const*) ; 

void libvlc_set_app_id(libvlc_instance_t *p_i, const char *id,
                       const char *version, const char *icon)
{
    libvlc_int_t *p_libvlc = p_i->p_libvlc_int;

    var_SetString(p_libvlc, "app-id", id ? id : "");
    var_SetString(p_libvlc, "app-version", version ? version : "");
    var_SetString(p_libvlc, "app-icon-name", icon ? icon : "");
}