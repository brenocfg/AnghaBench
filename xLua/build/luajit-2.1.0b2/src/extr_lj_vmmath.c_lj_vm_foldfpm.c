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

/* Variables and functions */
#define  IRFPM_CEIL 139 
#define  IRFPM_COS 138 
#define  IRFPM_EXP 137 
#define  IRFPM_EXP2 136 
#define  IRFPM_FLOOR 135 
#define  IRFPM_LOG 134 
#define  IRFPM_LOG10 133 
#define  IRFPM_LOG2 132 
#define  IRFPM_SIN 131 
#define  IRFPM_SQRT 130 
#define  IRFPM_TAN 129 
#define  IRFPM_TRUNC 128 
 double cos (double) ; 
 double exp (double) ; 
 double lj_vm_ceil (double) ; 
 double lj_vm_exp2 (double) ; 
 double lj_vm_floor (double) ; 
 double lj_vm_log2 (double) ; 
 double lj_vm_trunc (double) ; 
 double log (double) ; 
 double log10 (double) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 double sin (double) ; 
 double sqrt (double) ; 
 double tan (double) ; 

double lj_vm_foldfpm(double x, int fpm)
{
  switch (fpm) {
  case IRFPM_FLOOR: return lj_vm_floor(x);
  case IRFPM_CEIL: return lj_vm_ceil(x);
  case IRFPM_TRUNC: return lj_vm_trunc(x);
  case IRFPM_SQRT: return sqrt(x);
  case IRFPM_EXP: return exp(x);
  case IRFPM_EXP2: return lj_vm_exp2(x);
  case IRFPM_LOG: return log(x);
  case IRFPM_LOG2: return lj_vm_log2(x);
  case IRFPM_LOG10: return log10(x);
  case IRFPM_SIN: return sin(x);
  case IRFPM_COS: return cos(x);
  case IRFPM_TAN: return tan(x);
  default: lua_assert(0);
  }
  return 0;
}