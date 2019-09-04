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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ gboolean ;

/* Variables and functions */
 scalar_t__ verify_fs_object_json (char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ verify_seafdir_v0 (char const*,int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static gboolean
verify_seafdir (const char *dir_id, uint8_t *data, int len,
                gboolean verify_id, gboolean is_json)
{
    if (is_json)
        return verify_fs_object_json (dir_id, data, len);
    else
        return verify_seafdir_v0 (dir_id, data, len, verify_id);
}