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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {char const* text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  int /*<<< orphan*/  guint8 ;
typedef  int /*<<< orphan*/  SeafDir ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loadb (char const*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ seaf_decompress (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/ * seaf_dir_from_json_object (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 

__attribute__((used)) static SeafDir *
seaf_dir_from_json (const char *dir_id, uint8_t *data, int len)
{
    guint8 *decompressed;
    int outlen;
    json_t *object = NULL;
    json_error_t error;
    SeafDir *dir;

    if (seaf_decompress (data, len, &decompressed, &outlen) < 0) {
        seaf_warning ("Failed to decompress dir object %s.\n", dir_id);
        return NULL;
    }

    object = json_loadb ((const char *)decompressed, outlen, 0, &error);
    g_free (decompressed);
    if (!object) {
        seaf_warning ("Failed to load seafdir json object: %s.\n", error.text);
        return NULL;
    }

    dir = seaf_dir_from_json_object (dir_id, object);

    json_decref (object);
    return dir;
}