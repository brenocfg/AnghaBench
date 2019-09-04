#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct prime_ent {int /*<<< orphan*/  shift; int /*<<< orphan*/  inv; int /*<<< orphan*/  prime; } ;
typedef  TYPE_1__* htab_t ;
typedef  int /*<<< orphan*/  hashval_t ;
struct TYPE_3__ {size_t size_prime_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  htab_mod_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct prime_ent* prime_tab ; 

__attribute__((used)) static inline hashval_t
htab_mod (hashval_t hash, htab_t htab)
{
  const struct prime_ent *p = &prime_tab[htab->size_prime_index];
  return htab_mod_1 (hash, p->prime, p->inv, p->shift);
}