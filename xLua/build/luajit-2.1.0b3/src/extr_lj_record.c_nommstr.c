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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  jit_State ;
typedef  int /*<<< orphan*/  TRef ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 int /*<<< orphan*/  IR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  J2G (int /*<<< orphan*/ *) ; 
 scalar_t__ MM_FAST ; 
 int /*<<< orphan*/ * ir_kstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmname_str (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tref_isk (int /*<<< orphan*/ ) ; 
 scalar_t__ tref_isstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tref_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nommstr(jit_State *J, TRef key)
{
  if (tref_isstr(key)) {
    if (tref_isk(key)) {
      GCstr *str = ir_kstr(IR(tref_ref(key)));
      uint32_t mm;
      for (mm = 0; mm <= MM_FAST; mm++)
	if (mmname_str(J2G(J), mm) == str)
	  return 0;  /* MUST be one the fast metamethod names. */
    } else {
      return 0;  /* Variable string key MAY be a metamethod name. */
    }
  }
  return 1;  /* CANNOT be a metamethod name. */
}