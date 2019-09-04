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
struct TYPE_3__ {char const* text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  int /*<<< orphan*/  guint8 ;
typedef  int /*<<< orphan*/  Seafile ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loadb (char const*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ seaf_decompress (void*,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 
 int /*<<< orphan*/ * seafile_from_json_object (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Seafile *
seafile_from_json (const char *id, void *data, int len)
{
    guint8 *decompressed;
    int outlen;
    json_t *object = NULL;
    json_error_t error;
    Seafile *seafile;

    if (seaf_decompress (data, len, &decompressed, &outlen) < 0) {
        seaf_warning ("Failed to decompress seafile object %s.\n", id);
        return NULL;
    }

    object = json_loadb ((const char *)decompressed, outlen, 0, &error);
    g_free (decompressed);
    if (!object) {
        seaf_warning ("Failed to load seafile json object: %s.\n", error.text);
        return NULL;
    }

    seafile = seafile_from_json_object (id, object);

    json_decref (object);
    return seafile;
}