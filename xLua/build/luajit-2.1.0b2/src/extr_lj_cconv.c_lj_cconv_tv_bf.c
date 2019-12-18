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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  L; } ;
struct TYPE_5__ {int info; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ CType ;
typedef  TYPE_2__ CTState ;
typedef  int CTSize ;
typedef  int CTInfo ;

/* Variables and functions */
 int CTF_BOOL ; 
 int CTF_UNSIGNED ; 
 int /*<<< orphan*/  LJ_DUALNUM ; 
 int /*<<< orphan*/  LJ_ERR_FFI_NYIPACKBIT ; 
 int ctype_bitbsz (int) ; 
 int ctype_bitcsz (int) ; 
 int ctype_bitpos (int) ; 
 int ctype_isbitfield (int) ; 
 int /*<<< orphan*/  lj_err_caller (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  setboolV (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setintV (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setnumV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int lj_cconv_tv_bf(CTState *cts, CType *s, TValue *o, uint8_t *sp)
{
  CTInfo info = s->info;
  CTSize pos, bsz;
  uint32_t val;
  lua_assert(ctype_isbitfield(info));
  /* NYI: packed bitfields may cause misaligned reads. */
  switch (ctype_bitcsz(info)) {
  case 4: val = *(uint32_t *)sp; break;
  case 2: val = *(uint16_t *)sp; break;
  case 1: val = *(uint8_t *)sp; break;
  default: lua_assert(0); val = 0; break;
  }
  /* Check if a packed bitfield crosses a container boundary. */
  pos = ctype_bitpos(info);
  bsz = ctype_bitbsz(info);
  lua_assert(pos < 8*ctype_bitcsz(info));
  lua_assert(bsz > 0 && bsz <= 8*ctype_bitcsz(info));
  if (pos + bsz > 8*ctype_bitcsz(info))
    lj_err_caller(cts->L, LJ_ERR_FFI_NYIPACKBIT);
  if (!(info & CTF_BOOL)) {
    CTSize shift = 32 - bsz;
    if (!(info & CTF_UNSIGNED)) {
      setintV(o, (int32_t)(val << (shift-pos)) >> shift);
    } else {
      val = (val << (shift-pos)) >> shift;
      if (!LJ_DUALNUM || (int32_t)val < 0)
	setnumV(o, (lua_Number)(uint32_t)val);
      else
	setintV(o, (int32_t)val);
    }
  } else {
    lua_assert(bsz == 1);
    setboolV(o, (val >> pos) & 1);
  }
  return 0;  /* No GC step needed. */
}