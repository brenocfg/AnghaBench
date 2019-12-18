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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  Object ;
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash64 (void const*,int /*<<< orphan*/ ) ; 
 int journal_file_find_data_object_with_hash (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int journal_file_find_data_object(
                JournalFile *f,
                const void *data, uint64_t size,
                Object **ret, uint64_t *offset) {

        uint64_t hash;

        assert(f);
        assert(data || size == 0);

        hash = hash64(data, size);

        return journal_file_find_data_object_with_hash(f,
                                                       data, size, hash,
                                                       ret, offset);
}