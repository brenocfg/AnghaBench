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
struct TYPE_3__ {char* member_0; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  const member_2; int /*<<< orphan*/  const member_1; } ;
typedef  int /*<<< orphan*/  JsonVariant ;
typedef  int /*<<< orphan*/  JsonDispatchFlags ;
typedef  TYPE_1__ JsonDispatch ;

/* Variables and functions */
#define  JSON_VARIANT_OBJECT 129 
 int json_dispatch (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
#define  oci_hooks_array 128 
 int /*<<< orphan*/  oci_unexpected ; 

__attribute__((used)) static int oci_hooks(const char *name, JsonVariant *v, JsonDispatchFlags flags, void *userdata) {

        static const JsonDispatch table[] = {
                { "prestart",  JSON_VARIANT_OBJECT, oci_hooks_array, 0, 0 },
                { "poststart", JSON_VARIANT_OBJECT, oci_hooks_array, 0, 0 },
                { "poststop",  JSON_VARIANT_OBJECT, oci_hooks_array, 0, 0 },
                {}
        };

        return json_dispatch(v, table, oci_unexpected, flags, userdata);
}