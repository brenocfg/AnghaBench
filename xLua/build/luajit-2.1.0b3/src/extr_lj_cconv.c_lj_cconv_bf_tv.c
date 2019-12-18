#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  L; } ;
struct TYPE_7__ {int info; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_1__ CType ;
typedef  TYPE_2__ CTState ;
typedef  int CTSize ;
typedef  int CTInfo ;

/* Variables and functions */
 int CTF_BOOL ; 
 int CTF_UNSIGNED ; 
 int /*<<< orphan*/  CTID_BOOL ; 
 int /*<<< orphan*/  CTID_INT32 ; 
 int /*<<< orphan*/  CTID_UINT32 ; 
 int /*<<< orphan*/  LJ_ERR_FFI_NYIPACKBIT ; 
 int ctype_bitbsz (int) ; 
 int ctype_bitcsz (int) ; 
 int ctype_bitpos (int) ; 
 int /*<<< orphan*/  ctype_get (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ctype_isbitfield (int) ; 
 int /*<<< orphan*/  lj_cconv_ct_tv (TYPE_2__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_err_caller (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

void lj_cconv_bf_tv(CTState *cts, CType *d, uint8_t *dp, TValue *o)
{
  CTInfo info = d->info;
  CTSize pos, bsz;
  uint32_t val, mask;
  lua_assert(ctype_isbitfield(info));
  if ((info & CTF_BOOL)) {
    uint8_t tmpbool;
    lua_assert(ctype_bitbsz(info) == 1);
    lj_cconv_ct_tv(cts, ctype_get(cts, CTID_BOOL), &tmpbool, o, 0);
    val = tmpbool;
  } else {
    CTypeID did = (info & CTF_UNSIGNED) ? CTID_UINT32 : CTID_INT32;
    lj_cconv_ct_tv(cts, ctype_get(cts, did), (uint8_t *)&val, o, 0);
  }
  pos = ctype_bitpos(info);
  bsz = ctype_bitbsz(info);
  lua_assert(pos < 8*ctype_bitcsz(info));
  lua_assert(bsz > 0 && bsz <= 8*ctype_bitcsz(info));
  /* Check if a packed bitfield crosses a container boundary. */
  if (pos + bsz > 8*ctype_bitcsz(info))
    lj_err_caller(cts->L, LJ_ERR_FFI_NYIPACKBIT);
  mask = ((1u << bsz) - 1u) << pos;
  val = (val << pos) & mask;
  /* NYI: packed bitfields may cause misaligned reads/writes. */
  switch (ctype_bitcsz(info)) {
  case 4: *(uint32_t *)dp = (*(uint32_t *)dp & ~mask) | (uint32_t)val; break;
  case 2: *(uint16_t *)dp = (*(uint16_t *)dp & ~mask) | (uint16_t)val; break;
  case 1: *(uint8_t *)dp = (*(uint8_t *)dp & ~mask) | (uint8_t)val; break;
  default: lua_assert(0); break;
  }
}