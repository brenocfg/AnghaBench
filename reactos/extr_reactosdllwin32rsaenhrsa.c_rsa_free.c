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
struct TYPE_3__ {int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  qP; int /*<<< orphan*/  dP; int /*<<< orphan*/  dQ; int /*<<< orphan*/  N; int /*<<< orphan*/  d; int /*<<< orphan*/  e; } ;
typedef  TYPE_1__ rsa_key ;

/* Variables and functions */
 int /*<<< orphan*/  mp_clear_multi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void rsa_free(rsa_key *key)
{
   mp_clear_multi(&key->e, &key->d, &key->N, &key->dQ, &key->dP,
                  &key->qP, &key->p, &key->q, NULL);
}