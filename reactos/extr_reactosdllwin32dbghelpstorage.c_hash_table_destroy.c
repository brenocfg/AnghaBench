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
struct hash_table {int dummy; } ;

/* Variables and functions */

void hash_table_destroy(struct hash_table* ht)
{
#if defined(USE_STATS)
    int                         i;
    unsigned                    len;
    unsigned                    min = 0xffffffff, max = 0, sq = 0;
    struct hash_table_elt*      elt;
    double                      mean, variance;

    for (i = 0; i < ht->num_buckets; i++)
    {
        for (len = 0, elt = ht->buckets[i]; elt; elt = elt->next) len++;
        if (len < min) min = len;
        if (len > max) max = len;
        sq += len * len;
    }
    mean = (double)ht->num_elts / ht->num_buckets;
    variance = (double)sq / ht->num_buckets - mean * mean;
    FIXME("STATS: elts[num:%-4u size:%u mean:%f] buckets[min:%-4u variance:%+f max:%-4u]\n",
          ht->num_elts, ht->num_buckets, mean, min, variance, max);

    for (i = 0; i < ht->num_buckets; i++)
    {
        for (len = 0, elt = ht->buckets[i]; elt; elt = elt->next) len++;
        if (len == max)
        {
            FIXME("Longest bucket:\n");
            for (elt = ht->buckets[i]; elt; elt = elt->next)
                FIXME("\t%s\n", elt->name);
            break;
        }

    }
#endif
}