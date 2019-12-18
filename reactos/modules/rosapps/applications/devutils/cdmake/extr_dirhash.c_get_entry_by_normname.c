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
struct target_dir_hash {struct target_dir_entry** buckets; } ;
struct target_dir_entry {struct target_dir_entry* next_dir_hash_entry; int /*<<< orphan*/  normalized_name; } ;

/* Variables and functions */
 unsigned int NUM_DIR_HASH_BUCKETS ; 
 unsigned int djb_hash (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct target_dir_entry *
get_entry_by_normname(struct target_dir_hash *dh, const char *norm)
{
    unsigned int hashcode;
    struct target_dir_entry *de;
    hashcode = djb_hash(norm);
    de = dh->buckets[hashcode % NUM_DIR_HASH_BUCKETS];
    while (de && strcmp(de->normalized_name, norm))
        de = de->next_dir_hash_entry;
    return de;
}