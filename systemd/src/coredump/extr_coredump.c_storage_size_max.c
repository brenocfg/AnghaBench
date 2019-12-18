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

/* Variables and functions */
 scalar_t__ COREDUMP_STORAGE_EXTERNAL ; 
 scalar_t__ COREDUMP_STORAGE_JOURNAL ; 
 scalar_t__ COREDUMP_STORAGE_NONE ; 
 int /*<<< orphan*/  arg_external_size_max ; 
 int /*<<< orphan*/  arg_journal_size_max ; 
 scalar_t__ arg_storage ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static uint64_t storage_size_max(void) {
        if (arg_storage == COREDUMP_STORAGE_EXTERNAL)
                return arg_external_size_max;
        if (arg_storage == COREDUMP_STORAGE_JOURNAL)
                return arg_journal_size_max;
        assert(arg_storage == COREDUMP_STORAGE_NONE);
        return 0;
}