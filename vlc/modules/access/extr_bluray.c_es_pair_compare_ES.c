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
struct TYPE_3__ {int /*<<< orphan*/  const* p_es; } ;
typedef  TYPE_1__ es_pair_t ;
typedef  int /*<<< orphan*/  es_out_id_t ;

/* Variables and functions */

__attribute__((used)) static bool es_pair_compare_ES(const es_pair_t *p_pair, const void *p_es)
{
    return p_pair->p_es == (const es_out_id_t *)p_es;
}