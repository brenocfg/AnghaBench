#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int num_elts; } ;
struct sparse_array {int /*<<< orphan*/  key2index; TYPE_1__ elements; } ;
struct key2index {unsigned long key; } ;

/* Variables and functions */
 struct key2index* vector_at (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static struct key2index* sparse_array_lookup(const struct sparse_array* sa,
                                             unsigned long key, unsigned* idx)
{
    struct key2index*   pk2i;
    unsigned            low, high;

    if (!sa->elements.num_elts)
    {
        *idx = 0;
        return NULL;
    }
    high = sa->elements.num_elts;
    pk2i = vector_at(&sa->key2index, high - 1);
    if (pk2i->key < key)
    {
        *idx = high;
        return NULL;
    }
    if (pk2i->key == key)
    {
        *idx = high - 1;
        return pk2i;
    }
    low = 0;
    pk2i = vector_at(&sa->key2index, low);
    if (pk2i->key >= key)
    {
        *idx = 0;
        return pk2i;
    }
    /* now we have: sa(lowest key) < key < sa(highest key) */
    while (low < high)
    {
        *idx = (low + high) / 2;
        pk2i = vector_at(&sa->key2index, *idx);
        if (pk2i->key > key)            high = *idx;
        else if (pk2i->key < key)       low = *idx + 1;
        else                            return pk2i;
    }
    /* binary search could return exact item, we search for highest one
     * below the key
     */
    if (pk2i->key < key)
        pk2i = vector_at(&sa->key2index, ++(*idx));
    return pk2i;
}