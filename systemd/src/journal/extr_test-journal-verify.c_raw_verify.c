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
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  journal_file_close (int /*<<< orphan*/ *) ; 
 int journal_file_open (int,char const*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int journal_file_verify (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int raw_verify(const char *fn, const char *verification_key) {
        JournalFile *f;
        int r;

        r = journal_file_open(-1, fn, O_RDONLY, 0666, true, (uint64_t) -1, !!verification_key, NULL, NULL, NULL, NULL, &f);
        if (r < 0)
                return r;

        r = journal_file_verify(f, verification_key, NULL, NULL, NULL, false);
        (void) journal_file_close(f);

        return r;
}