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
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  journal_file_set_offline_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  pthread_setname_np (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void * journal_file_set_offline_thread(void *arg) {
        JournalFile *f = arg;

        (void) pthread_setname_np(pthread_self(), "journal-offline");

        journal_file_set_offline_internal(f);

        return NULL;
}