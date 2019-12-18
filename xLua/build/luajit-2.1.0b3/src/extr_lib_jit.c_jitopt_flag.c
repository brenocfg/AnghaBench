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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ jit_State ;

/* Variables and functions */
 char* JIT_F_OPTSTRING ; 
 int JIT_F_OPT_FIRST ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int jitopt_flag(jit_State *J, const char *str)
{
  const char *lst = JIT_F_OPTSTRING;
  uint32_t opt;
  int set = 1;
  if (str[0] == '+') {
    str++;
  } else if (str[0] == '-') {
    str++;
    set = 0;
  } else if (str[0] == 'n' && str[1] == 'o') {
    str += str[2] == '-' ? 3 : 2;
    set = 0;
  }
  for (opt = JIT_F_OPT_FIRST; ; opt <<= 1) {
    size_t len = *(const uint8_t *)lst;
    if (len == 0)
      break;
    if (strncmp(str, lst+1, len) == 0 && str[len] == '\0') {
      if (set) J->flags |= opt; else J->flags &= ~opt;
      return 1;  /* Ok. */
    }
    lst += 1+len;
  }
  return 0;  /* No match. */
}