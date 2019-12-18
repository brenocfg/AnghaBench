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
typedef  void guint8 ;
struct TYPE_5__ {scalar_t__ version; int /*<<< orphan*/  dir_id; } ;
typedef  TYPE_1__ SeafDir ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (void*) ; 
 scalar_t__ seaf_compress (void*,int,void**,int*) ; 
 void* seaf_dir_to_json (TYPE_1__*,int*) ; 
 void* seaf_dir_to_v0_data (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 

void *
seaf_dir_to_data (SeafDir *dir, int *len)
{
    if (dir->version > 0) {
        guint8 *data;
        int orig_len;
        guint8 *compressed;

        data = seaf_dir_to_json (dir, &orig_len);
        if (!data)
            return NULL;

        if (seaf_compress (data, orig_len, &compressed, len) < 0) {
            seaf_warning ("Failed to compress dir object %s.\n", dir->dir_id);
            g_free (data);
            return NULL;
        }

        g_free (data);
        return compressed;
    } else
        return seaf_dir_to_v0_data (dir, len);
}