#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {int /*<<< orphan*/  items; } ;
struct TYPE_9__ {TYPE_1__* header; int /*<<< orphan*/  seal; } ;
struct TYPE_8__ {int /*<<< orphan*/  data_hash_table_offset; int /*<<< orphan*/  field_hash_table_offset; } ;
typedef  TYPE_2__ JournalFile ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OBJECT_DATA_HASH_TABLE ; 
 int /*<<< orphan*/  OBJECT_FIELD_HASH_TABLE ; 
 int /*<<< orphan*/  Object ; 
 TYPE_7__ hash_table ; 
 int journal_file_append_tag (TYPE_2__*) ; 
 int journal_file_hmac_put_header (TYPE_2__*) ; 
 int journal_file_hmac_put_object (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int journal_file_append_first_tag(JournalFile *f) {
        int r;
        uint64_t p;

        if (!f->seal)
                return 0;

        log_debug("Calculating first tag...");

        r = journal_file_hmac_put_header(f);
        if (r < 0)
                return r;

        p = le64toh(f->header->field_hash_table_offset);
        if (p < offsetof(Object, hash_table.items))
                return -EINVAL;
        p -= offsetof(Object, hash_table.items);

        r = journal_file_hmac_put_object(f, OBJECT_FIELD_HASH_TABLE, NULL, p);
        if (r < 0)
                return r;

        p = le64toh(f->header->data_hash_table_offset);
        if (p < offsetof(Object, hash_table.items))
                return -EINVAL;
        p -= offsetof(Object, hash_table.items);

        r = journal_file_hmac_put_object(f, OBJECT_DATA_HASH_TABLE, NULL, p);
        if (r < 0)
                return r;

        r = journal_file_append_tag(f);
        if (r < 0)
                return r;

        return 0;
}