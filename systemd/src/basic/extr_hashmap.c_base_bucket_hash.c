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
typedef  int uint64_t ;
struct siphash {int dummy; } ;
struct TYPE_7__ {TYPE_1__* hash_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* hash ) (void const*,struct siphash*) ;} ;
typedef  TYPE_2__ HashmapBase ;

/* Variables and functions */
 int /*<<< orphan*/  hash_key (TYPE_2__*) ; 
 int n_buckets (TYPE_2__*) ; 
 int siphash24_finalize (struct siphash*) ; 
 int /*<<< orphan*/  siphash24_init (struct siphash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void const*,struct siphash*) ; 

__attribute__((used)) static unsigned base_bucket_hash(HashmapBase *h, const void *p) {
        struct siphash state;
        uint64_t hash;

        siphash24_init(&state, hash_key(h));

        h->hash_ops->hash(p, &state);

        hash = siphash24_finalize(&state);

        return (unsigned) (hash % n_buckets(h));
}