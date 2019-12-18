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
struct sym_key {scalar_t__ len; int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  khint_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static khint_t
sym_eq(struct sym_key a, struct sym_key b)
{
  if (a.len != b.len) return FALSE;
  if (memcmp(a.ptr, b.ptr, a.len) == 0) return TRUE;
  return FALSE;
}