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
struct TYPE_6__ {int /*<<< orphan*/  head_commit; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  is_corrupt; } ;
typedef  TYPE_2__ CheckHeadData ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loadb (char const*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ json_object_get_int_member (int /*<<< orphan*/ *,char*) ; 
 char* json_object_get_string_member (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ json_object_has_member (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_head_commit_info (const char *rsp_content, int rsp_size, CheckHeadData *data)
{
    json_t *object = NULL;
    json_error_t jerror;
    const char *head_commit;

    object = json_loadb (rsp_content, rsp_size, 0, &jerror);
    if (!object) {
        seaf_warning ("Parse response failed: %s.\n", jerror.text);
        return -1;
    }

    if (json_object_has_member (object, "is_corrupted") &&
        json_object_get_int_member (object, "is_corrupted"))
        data->is_corrupt = TRUE;

    if (!data->is_corrupt) {
        head_commit = json_object_get_string_member (object, "head_commit_id");
        if (!head_commit) {
            seaf_warning ("Check head commit for repo %s failed. "
                          "Response doesn't contain head commit id.\n",
                          data->repo_id);
            json_decref (object);
            return -1;
        }
        memcpy (data->head_commit, head_commit, 40);
    }

    json_decref (object);
    return 0;
}