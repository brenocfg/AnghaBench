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
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  int gsize ;
typedef  int /*<<< orphan*/  SeafCommit ;

/* Variables and functions */
 int /*<<< orphan*/  clean_utf8_data (char*,int) ; 
 int /*<<< orphan*/ * commit_from_json_object (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loadb (char*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 

SeafCommit *
seaf_commit_from_data (const char *id, char *data, gsize len)
{
    json_t *object;
    SeafCommit *commit;
    json_error_t jerror;

    object = json_loadb (data, len, 0, &jerror);
    if (!object) {
        /* Perhaps the commit object contains invalid UTF-8 character. */
        if (data[len-1] == 0)
            clean_utf8_data (data, len - 1);
        else
            clean_utf8_data (data, len);

        object = json_loadb (data, len, 0, &jerror);
        if (!object) {
            seaf_warning ("Failed to load commit json: %s.\n", jerror.text);
            return NULL;
        }
    }

    commit = commit_from_json_object (id, object);

    json_decref (object);

    return commit;
}