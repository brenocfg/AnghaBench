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
typedef  int /*<<< orphan*/  VarlinkReplyFlags ;
typedef  int /*<<< orphan*/  Varlink ;
typedef  int /*<<< orphan*/  JsonVariant ;

/* Variables and functions */
 int JSON_FORMAT_NEWLINE ; 
 int JSON_FORMAT_PRETTY ; 
 int /*<<< orphan*/  json_variant_dump (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  null ; 

__attribute__((used)) static int reply_callback(Varlink *v, JsonVariant *p, const char *error_id, VarlinkReplyFlags flags, void *userdata) {
        json_variant_dump(p, JSON_FORMAT_NEWLINE|JSON_FORMAT_PRETTY, null, NULL);
        return 0;
}