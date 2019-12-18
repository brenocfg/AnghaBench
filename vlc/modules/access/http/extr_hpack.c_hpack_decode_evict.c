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
struct hpack_decoder {scalar_t__ size; scalar_t__ max_size; size_t entries; scalar_t__* table; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 size_t strlen (scalar_t__) ; 

__attribute__((used)) static void hpack_decode_evict(struct hpack_decoder *dec)
{
    /* Eviction: count how many entries to evict */
    size_t evicted = 0;
    while (dec->size > dec->max_size)
    {
        assert(evicted < dec->entries);

        size_t namelen = strlen(dec->table[evicted]);
        size_t valuelen = strlen(dec->table[evicted] + namelen + 1);

        assert(dec->size >= 32 + namelen + valuelen);
        dec->size -= 32 + namelen + valuelen;
        evicted++;
    }

    /* Eviction: remove oldest entries */
    if (evicted > 0)
    {
        for (size_t i = 0; i < evicted; i++)
            free(dec->table[i]);

        dec->entries -= evicted;
        memmove(dec->table, dec->table + evicted,
                sizeof (dec->table[0]) * dec->entries);
    }
}