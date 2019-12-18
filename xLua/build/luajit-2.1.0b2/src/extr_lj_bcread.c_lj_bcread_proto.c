#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_20__ {int sizebc; int sizekgc; int sizekn; int sizept; int firstline; int numline; int /*<<< orphan*/  varinfo; int /*<<< orphan*/  uvinfo; int /*<<< orphan*/  lineinfo; int /*<<< orphan*/  chunkname; scalar_t__ trace; void* flags; void* sizeuv; int /*<<< orphan*/  uv; int /*<<< orphan*/  k; void* framesize; void* numparams; int /*<<< orphan*/  gct; } ;
struct TYPE_19__ {int /*<<< orphan*/  chunkname; int /*<<< orphan*/  L; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int MSize ;
typedef  TYPE_1__ LexState ;
typedef  TYPE_2__ GCproto ;
typedef  int /*<<< orphan*/  GCRef ;
typedef  int BCLine ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 int BCDUMP_F_STRIP ; 
 int /*<<< orphan*/  LJ_TPROTO ; 
 int bcread_byte (TYPE_1__*) ; 
 int /*<<< orphan*/  bcread_bytecode (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  bcread_dbg (TYPE_1__*,TYPE_2__*,int) ; 
 int bcread_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  bcread_kgc (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  bcread_knum (TYPE_1__*,TYPE_2__*,int) ; 
 int bcread_uleb128 (TYPE_1__*) ; 
 int /*<<< orphan*/  bcread_uv (TYPE_1__*,TYPE_2__*,int) ; 
 char* bcread_varinfo (TYPE_2__*) ; 
 scalar_t__ lj_mem_newgco (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obj2gco (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgcref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setmref (int /*<<< orphan*/ ,char*) ; 

GCproto *lj_bcread_proto(LexState *ls)
{
  GCproto *pt;
  MSize framesize, numparams, flags, sizeuv, sizekgc, sizekn, sizebc, sizept;
  MSize ofsk, ofsuv, ofsdbg;
  MSize sizedbg = 0;
  BCLine firstline = 0, numline = 0;

  /* Read prototype header. */
  flags = bcread_byte(ls);
  numparams = bcread_byte(ls);
  framesize = bcread_byte(ls);
  sizeuv = bcread_byte(ls);
  sizekgc = bcread_uleb128(ls);
  sizekn = bcread_uleb128(ls);
  sizebc = bcread_uleb128(ls) + 1;
  if (!(bcread_flags(ls) & BCDUMP_F_STRIP)) {
    sizedbg = bcread_uleb128(ls);
    if (sizedbg) {
      firstline = bcread_uleb128(ls);
      numline = bcread_uleb128(ls);
    }
  }

  /* Calculate total size of prototype including all colocated arrays. */
  sizept = (MSize)sizeof(GCproto) +
	   sizebc*(MSize)sizeof(BCIns) +
	   sizekgc*(MSize)sizeof(GCRef);
  sizept = (sizept + (MSize)sizeof(TValue)-1) & ~((MSize)sizeof(TValue)-1);
  ofsk = sizept; sizept += sizekn*(MSize)sizeof(TValue);
  ofsuv = sizept; sizept += ((sizeuv+1)&~1)*2;
  ofsdbg = sizept; sizept += sizedbg;

  /* Allocate prototype object and initialize its fields. */
  pt = (GCproto *)lj_mem_newgco(ls->L, (MSize)sizept);
  pt->gct = ~LJ_TPROTO;
  pt->numparams = (uint8_t)numparams;
  pt->framesize = (uint8_t)framesize;
  pt->sizebc = sizebc;
  setmref(pt->k, (char *)pt + ofsk);
  setmref(pt->uv, (char *)pt + ofsuv);
  pt->sizekgc = 0;  /* Set to zero until fully initialized. */
  pt->sizekn = sizekn;
  pt->sizept = sizept;
  pt->sizeuv = (uint8_t)sizeuv;
  pt->flags = (uint8_t)flags;
  pt->trace = 0;
  setgcref(pt->chunkname, obj2gco(ls->chunkname));

  /* Close potentially uninitialized gap between bc and kgc. */
  *(uint32_t *)((char *)pt + ofsk - sizeof(GCRef)*(sizekgc+1)) = 0;

  /* Read bytecode instructions and upvalue refs. */
  bcread_bytecode(ls, pt, sizebc);
  bcread_uv(ls, pt, sizeuv);

  /* Read constants. */
  bcread_kgc(ls, pt, sizekgc);
  pt->sizekgc = sizekgc;
  bcread_knum(ls, pt, sizekn);

  /* Read and initialize debug info. */
  pt->firstline = firstline;
  pt->numline = numline;
  if (sizedbg) {
    MSize sizeli = (sizebc-1) << (numline < 256 ? 0 : numline < 65536 ? 1 : 2);
    setmref(pt->lineinfo, (char *)pt + ofsdbg);
    setmref(pt->uvinfo, (char *)pt + ofsdbg + sizeli);
    bcread_dbg(ls, pt, sizedbg);
    setmref(pt->varinfo, bcread_varinfo(pt));
  } else {
    setmref(pt->lineinfo, NULL);
    setmref(pt->uvinfo, NULL);
    setmref(pt->varinfo, NULL);
  }
  return pt;
}