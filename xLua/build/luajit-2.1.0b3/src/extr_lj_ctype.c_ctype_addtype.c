#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {scalar_t__* hash; } ;
struct TYPE_5__ {scalar_t__ next; int /*<<< orphan*/  size; int /*<<< orphan*/  info; } ;
typedef  scalar_t__ CTypeID1 ;
typedef  scalar_t__ CTypeID ;
typedef  TYPE_1__ CType ;
typedef  TYPE_2__ CTState ;

/* Variables and functions */
 size_t ct_hashtype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctype_addtype(CTState *cts, CType *ct, CTypeID id)
{
  uint32_t h = ct_hashtype(ct->info, ct->size);
  ct->next = cts->hash[h];
  cts->hash[h] = (CTypeID1)id;
}