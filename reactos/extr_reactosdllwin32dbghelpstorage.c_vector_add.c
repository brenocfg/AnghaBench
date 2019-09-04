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
struct vector {unsigned int num_elts; unsigned int num_buckets; unsigned int shift; int buckets_allocated; void** buckets; unsigned int elt_size; } ;
struct pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (void*,void**,int) ; 
 void* pool_alloc (struct pool*,unsigned int) ; 
 void* vector_at (struct vector*,unsigned int) ; 

void* vector_add(struct vector* v, struct pool* pool)
{
    unsigned    ncurr = v->num_elts++;

    /* check that we don't wrap around */
    assert(v->num_elts > ncurr);
    if (ncurr == (v->num_buckets << v->shift))
    {
        if(v->num_buckets == v->buckets_allocated)
        {
            /* Double the bucket cache, so it scales well with big vectors.*/
            unsigned    new_reserved;
            void*       new;

            new_reserved = 2*v->buckets_allocated;
            if(new_reserved == 0) new_reserved = 1;

            /* Don't even try to resize memory.
               Pool datastructure is very inefficient with reallocs. */
            new = pool_alloc(pool, new_reserved * sizeof(void*));
            memcpy(new, v->buckets, v->buckets_allocated * sizeof(void*));
            v->buckets = new;
            v->buckets_allocated = new_reserved;
        }
        v->buckets[v->num_buckets] = pool_alloc(pool, v->elt_size << v->shift);
        return v->buckets[v->num_buckets++];
    }
    return vector_at(v, ncurr);
}