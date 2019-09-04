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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ local_ref_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int strcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int local_ref_cmp(const void *key, const void *ref)
{
    return strcmpW((const WCHAR*)key, ((const local_ref_t*)ref)->name);
}