#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_5__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
struct TYPE_6__ {int version; } ;
typedef  TYPE_2__ CheckProtocolData ;

/* Variables and functions */
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loadb (char const*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int json_object_get_int_member (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ json_object_has_member (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 

__attribute__((used)) static int
parse_protocol_version (const char *rsp_content, int rsp_size, CheckProtocolData *data)
{
    json_t *object = NULL;
    json_error_t jerror;
    int version;

    object = json_loadb (rsp_content, rsp_size, 0, &jerror);
    if (!object) {
        seaf_warning ("Parse response failed: %s.\n", jerror.text);
        return -1;
    }

    if (json_object_has_member (object, "version")) {
        version = json_object_get_int_member (object, "version");
        data->version = version;
    } else {
        seaf_warning ("Response doesn't contain protocol version.\n");
        json_decref (object);
        return -1;
    }

    json_decref (object);
    return 0;
}