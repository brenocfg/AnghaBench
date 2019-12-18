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
typedef  int /*<<< orphan*/  sd_id128_t ;
struct TYPE_5__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  boot_id; struct TYPE_5__* header; int /*<<< orphan*/  machine_id; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEDIUM ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync_directory_of_file (int /*<<< orphan*/ ) ; 
 int journal_file_set_online (TYPE_1__*) ; 
 int sd_id128_get_boot (int /*<<< orphan*/ *) ; 
 int sd_id128_get_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int journal_file_refresh_header(JournalFile *f) {
        sd_id128_t boot_id;
        int r;

        assert(f);
        assert(f->header);

        r = sd_id128_get_machine(&f->header->machine_id);
        if (IN_SET(r, -ENOENT, -ENOMEDIUM))
                /* We don't have a machine-id, let's continue without */
                zero(f->header->machine_id);
        else if (r < 0)
                return r;

        r = sd_id128_get_boot(&boot_id);
        if (r < 0)
                return r;

        f->header->boot_id = boot_id;

        r = journal_file_set_online(f);

        /* Sync the online state to disk */
        (void) fsync(f->fd);

        /* We likely just created a new file, also sync the directory this file is located in. */
        (void) fsync_directory_of_file(f->fd);

        return r;
}