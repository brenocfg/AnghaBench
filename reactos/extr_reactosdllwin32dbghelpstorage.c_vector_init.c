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
struct vector {unsigned int elt_size; int shift; scalar_t__ num_elts; scalar_t__ buckets_allocated; scalar_t__ num_buckets; int /*<<< orphan*/ * buckets; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void vector_init(struct vector* v, unsigned esz, unsigned bucket_sz)
{
    v->buckets = NULL;
    /* align size on DWORD boundaries */
    v->elt_size = (esz + 3) & ~3;
    switch (bucket_sz)
    {
    case    2: v->shift =  1; break;
    case    4: v->shift =  2; break;
    case    8: v->shift =  3; break;
    case   16: v->shift =  4; break;
    case   32: v->shift =  5; break;
    case   64: v->shift =  6; break;
    case  128: v->shift =  7; break;
    case  256: v->shift =  8; break;
    case  512: v->shift =  9; break;
    case 1024: v->shift = 10; break;
    default: assert(0);
    }
    v->num_buckets = 0;
    v->buckets_allocated = 0;
    v->num_elts = 0;
}