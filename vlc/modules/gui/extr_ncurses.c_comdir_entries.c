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
struct dir_entry_t {scalar_t__ file; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int comdir_entries(const void *a, const void *b)
{
    struct dir_entry_t *dir_entry1 = *(struct dir_entry_t**)a;
    struct dir_entry_t *dir_entry2 = *(struct dir_entry_t**)b;

    if (dir_entry1->file == dir_entry2->file)
        return strcasecmp(dir_entry1->path, dir_entry2->path);

    return dir_entry1->file ? 1 : -1;
}