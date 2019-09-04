#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guint8 ;
struct TYPE_5__ {scalar_t__ version; int /*<<< orphan*/  file_id; } ;
typedef  TYPE_1__ Seafile ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 scalar_t__ seaf_compress (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * seafile_to_json (TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * seafile_to_v0_data (TYPE_1__*,int*) ; 

__attribute__((used)) static guint8 *
seafile_to_data (Seafile *file, int *len)
{
    if (file->version > 0) {
        guint8 *data;
        int orig_len;
        guint8 *compressed;

        data = seafile_to_json (file, &orig_len);
        if (!data)
            return NULL;

        if (seaf_compress (data, orig_len, &compressed, len) < 0) {
            seaf_warning ("Failed to compress file object %s.\n", file->file_id);
            g_free (data);
            return NULL;
        }
        g_free (data);
        return compressed;
    } else
        return seafile_to_v0_data (file, len);
}