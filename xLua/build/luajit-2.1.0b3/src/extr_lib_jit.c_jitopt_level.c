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
typedef  int uint32_t ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ jit_State ;

/* Variables and functions */
 int JIT_F_OPT_0 ; 
 int JIT_F_OPT_1 ; 
 int JIT_F_OPT_2 ; 
 int JIT_F_OPT_3 ; 
 int JIT_F_OPT_MASK ; 

__attribute__((used)) static int jitopt_level(jit_State *J, const char *str)
{
  if (str[0] >= '0' && str[0] <= '9' && str[1] == '\0') {
    uint32_t flags;
    if (str[0] == '0') flags = JIT_F_OPT_0;
    else if (str[0] == '1') flags = JIT_F_OPT_1;
    else if (str[0] == '2') flags = JIT_F_OPT_2;
    else flags = JIT_F_OPT_3;
    J->flags = (J->flags & ~JIT_F_OPT_MASK) | flags;
    return 1;  /* Ok. */
  }
  return 0;  /* No match. */
}