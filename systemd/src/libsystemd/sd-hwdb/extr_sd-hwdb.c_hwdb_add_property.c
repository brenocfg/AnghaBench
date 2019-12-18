#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct trie_value_entry_f {int /*<<< orphan*/  key_off; } ;
struct trie_value_entry2_f {scalar_t__ file_priority; scalar_t__ filename_off; scalar_t__ line_number; } ;
struct TYPE_7__ {int properties_modified; int /*<<< orphan*/  properties; TYPE_1__* head; } ;
typedef  TYPE_2__ sd_hwdb ;
struct TYPE_6__ {int /*<<< orphan*/  value_entry_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int le64toh (int /*<<< orphan*/ ) ; 
 int ordered_hashmap_ensure_allocated (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct trie_value_entry2_f* ordered_hashmap_get (int /*<<< orphan*/ ,char const*) ; 
 int ordered_hashmap_replace (int /*<<< orphan*/ ,char const*,void*) ; 
 int /*<<< orphan*/  string_hash_ops ; 
 char* trie_string (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwdb_add_property(sd_hwdb *hwdb, const struct trie_value_entry_f *entry) {
        const char *key;
        int r;

        assert(hwdb);

        key = trie_string(hwdb, entry->key_off);

        /*
         * Silently ignore all properties which do not start with a
         * space; future extensions might use additional prefixes.
         */
        if (key[0] != ' ')
                return 0;

        key++;

        if (le64toh(hwdb->head->value_entry_size) >= sizeof(struct trie_value_entry2_f)) {
                const struct trie_value_entry2_f *old, *entry2;

                entry2 = (const struct trie_value_entry2_f *)entry;
                old = ordered_hashmap_get(hwdb->properties, key);
                if (old) {
                        /* On duplicates, we order by filename priority and line-number.
                         *
                         * v2 of the format had 64 bits for the line number.
                         * v3 reuses top 32 bits of line_number to store the priority.
                         * We check the top bits — if they are zero we have v2 format.
                         * This means that v2 clients will print wrong line numbers with
                         * v3 data.
                         *
                         * For v3 data: we compare the priority (of the source file)
                         * and the line number.
                         *
                         * For v2 data: we rely on the fact that the filenames in the hwdb
                         * are added in the order of priority (higher later), because they
                         * are *processed* in the order of priority. So we compare the
                         * indices to determine which file had higher priority. Comparing
                         * the strings alphabetically would be useless, because those are
                         * full paths, and e.g. /usr/lib would sort after /etc, even
                         * though it has lower priority. This is not reliable because of
                         * suffix compression, but should work for the most common case of
                         * /usr/lib/udev/hwbd.d and /etc/udev/hwdb.d, and is better than
                         * not doing the comparison at all.
                         */
                        bool lower;

                        if (entry2->file_priority == 0)
                                lower = entry2->filename_off < old->filename_off ||
                                        (entry2->filename_off == old->filename_off && entry2->line_number < old->line_number);
                        else
                                lower = entry2->file_priority < old->file_priority ||
                                        (entry2->file_priority == old->file_priority && entry2->line_number < old->line_number);
                        if (lower)
                                return 0;
                }
        }

        r = ordered_hashmap_ensure_allocated(&hwdb->properties, &string_hash_ops);
        if (r < 0)
                return r;

        r = ordered_hashmap_replace(hwdb->properties, key, (void *)entry);
        if (r < 0)
                return r;

        hwdb->properties_modified = true;

        return 0;
}