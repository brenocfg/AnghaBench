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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  GCproto ;
typedef  scalar_t__ BCReg ;
typedef  scalar_t__ BCOp ;
typedef  int /*<<< orphan*/  BCIns ;

/* Variables and functions */
 scalar_t__ BCMbase ; 
 scalar_t__ BCMdst ; 
#define  BC_GGET 131 
 scalar_t__ BC_KNIL ; 
#define  BC_MOV 130 
#define  BC_TGETS 129 
#define  BC_UGET 128 
 scalar_t__ LJ_FR2 ; 
 scalar_t__ bc_a (int /*<<< orphan*/ ) ; 
 scalar_t__ bc_b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bc_c (int /*<<< orphan*/ ) ; 
 scalar_t__ bc_d (int /*<<< orphan*/ ) ; 
 int const bc_op (int /*<<< orphan*/ ) ; 
 scalar_t__ bcmode_a (scalar_t__) ; 
 char* debug_varname (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gco2str (int /*<<< orphan*/ ) ; 
 char* lj_debug_uvname (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  const* proto_bc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proto_bcpos (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  proto_kgc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strdata (int /*<<< orphan*/ ) ; 

const char *lj_debug_slotname(GCproto *pt, const BCIns *ip, BCReg slot,
			      const char **name)
{
  const char *lname;
restart:
  lname = debug_varname(pt, proto_bcpos(pt, ip), slot);
  if (lname != NULL) { *name = lname; return "local"; }
  while (--ip > proto_bc(pt)) {
    BCIns ins = *ip;
    BCOp op = bc_op(ins);
    BCReg ra = bc_a(ins);
    if (bcmode_a(op) == BCMbase) {
      if (slot >= ra && (op != BC_KNIL || slot <= bc_d(ins)))
	return NULL;
    } else if (bcmode_a(op) == BCMdst && ra == slot) {
      switch (bc_op(ins)) {
      case BC_MOV:
	if (ra == slot) { slot = bc_d(ins); goto restart; }
	break;
      case BC_GGET:
	*name = strdata(gco2str(proto_kgc(pt, ~(ptrdiff_t)bc_d(ins))));
	return "global";
      case BC_TGETS:
	*name = strdata(gco2str(proto_kgc(pt, ~(ptrdiff_t)bc_c(ins))));
	if (ip > proto_bc(pt)) {
	  BCIns insp = ip[-1];
	  if (bc_op(insp) == BC_MOV && bc_a(insp) == ra+1+LJ_FR2 &&
	      bc_d(insp) == bc_b(ins))
	    return "method";
	}
	return "field";
      case BC_UGET:
	*name = lj_debug_uvname(pt, bc_d(ins));
	return "upvalue";
      default:
	return NULL;
      }
    }
  }
  return NULL;
}