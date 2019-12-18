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
struct TYPE_4__ {int /*<<< orphan*/  psz_string; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int intf_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int AddIntfCallback( vlc_object_t *obj, char const *var,
                            vlc_value_t old, vlc_value_t cur, void *data )
{
    int ret = intf_Create( vlc_object_instance(obj), cur.psz_string );
    if( ret )
        msg_Err( obj, "interface \"%s\" initialization failed",
                 cur.psz_string );

    (void) var; (void) old; (void) data;
    return ret;
}