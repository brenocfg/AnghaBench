#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {int needsp; int /*<<< orphan*/  cts; } ;
struct TYPE_16__ {int info; int size; } ;
struct TYPE_15__ {int size; } ;
typedef  int /*<<< orphan*/  CTypeID ;
typedef  TYPE_1__ CType ;
typedef  int CTSize ;
typedef  TYPE_2__ CTRepr ;
typedef  int CTInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_QUAL ; 
 int CTF_BOOL ; 
 int CTF_COMPLEX ; 
 int CTF_FP ; 
 int CTF_REF ; 
 int CTF_UCHAR ; 
 int CTF_UNION ; 
 int CTF_UNSIGNED ; 
 int CTF_VLA ; 
 int /*<<< orphan*/  CTID_CTYPEID ; 
 int CTSIZE_INVALID ; 
#define  CT_ARRAY 135 
#define  CT_ATTRIB 134 
#define  CT_ENUM 133 
#define  CT_FUNC 132 
#define  CT_NUM 131 
#define  CT_PTR 130 
#define  CT_STRUCT 129 
#define  CT_VOID 128 
 int /*<<< orphan*/  LJ_64 ; 
 int /*<<< orphan*/  ctype_appc (TYPE_2__*,char) ; 
 int /*<<< orphan*/  ctype_appnum (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ctype_attrib (int) ; 
 TYPE_11__* ctype_child (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ctype_cid (int) ; 
 TYPE_1__* ctype_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctype_isrefarray (int) ; 
 int /*<<< orphan*/  ctype_prepc (TYPE_2__*,char) ; 
 int /*<<< orphan*/  ctype_preplit (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ctype_prepnum (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ctype_prepqual (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ctype_preptype (TYPE_2__*,TYPE_1__*,int,char*) ; 
 int ctype_type (int) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctype_repr(CTRepr *ctr, CTypeID id)
{
  CType *ct = ctype_get(ctr->cts, id);
  CTInfo qual = 0;
  int ptrto = 0;
  for (;;) {
    CTInfo info = ct->info;
    CTSize size = ct->size;
    switch (ctype_type(info)) {
    case CT_NUM:
      if ((info & CTF_BOOL)) {
	ctype_preplit(ctr, "bool");
      } else if ((info & CTF_FP)) {
	if (size == sizeof(double)) ctype_preplit(ctr, "double");
	else if (size == sizeof(float)) ctype_preplit(ctr, "float");
	else ctype_preplit(ctr, "long double");
      } else if (size == 1) {
	if (!((info ^ CTF_UCHAR) & CTF_UNSIGNED)) ctype_preplit(ctr, "char");
	else if (CTF_UCHAR) ctype_preplit(ctr, "signed char");
	else ctype_preplit(ctr, "unsigned char");
      } else if (size < 8) {
	if (size == 4) ctype_preplit(ctr, "int");
	else ctype_preplit(ctr, "short");
	if ((info & CTF_UNSIGNED)) ctype_preplit(ctr, "unsigned");
      } else {
	ctype_preplit(ctr, "_t");
	ctype_prepnum(ctr, size*8);
	ctype_preplit(ctr, "int");
	if ((info & CTF_UNSIGNED)) ctype_prepc(ctr, 'u');
      }
      ctype_prepqual(ctr, (qual|info));
      return;
    case CT_VOID:
      ctype_preplit(ctr, "void");
      ctype_prepqual(ctr, (qual|info));
      return;
    case CT_STRUCT:
      ctype_preptype(ctr, ct, qual, (info & CTF_UNION) ? "union" : "struct");
      return;
    case CT_ENUM:
      if (id == CTID_CTYPEID) {
	ctype_preplit(ctr, "ctype");
	return;
      }
      ctype_preptype(ctr, ct, qual, "enum");
      return;
    case CT_ATTRIB:
      if (ctype_attrib(info) == CTA_QUAL) qual |= size;
      break;
    case CT_PTR:
      if ((info & CTF_REF)) {
	ctype_prepc(ctr, '&');
      } else {
	ctype_prepqual(ctr, (qual|info));
	if (LJ_64 && size == 4) ctype_preplit(ctr, "__ptr32");
	ctype_prepc(ctr, '*');
      }
      qual = 0;
      ptrto = 1;
      ctr->needsp = 1;
      break;
    case CT_ARRAY:
      if (ctype_isrefarray(info)) {
	ctr->needsp = 1;
	if (ptrto) { ptrto = 0; ctype_prepc(ctr, '('); ctype_appc(ctr, ')'); }
	ctype_appc(ctr, '[');
	if (size != CTSIZE_INVALID) {
	  CTSize csize = ctype_child(ctr->cts, ct)->size;
	  ctype_appnum(ctr, csize ? size/csize : 0);
	} else if ((info & CTF_VLA)) {
	  ctype_appc(ctr, '?');
	}
	ctype_appc(ctr, ']');
      } else if ((info & CTF_COMPLEX)) {
	if (size == 2*sizeof(float)) ctype_preplit(ctr, "float");
	ctype_preplit(ctr, "complex");
	return;
      } else {
	ctype_preplit(ctr, ")))");
	ctype_prepnum(ctr, size);
	ctype_preplit(ctr, "__attribute__((vector_size(");
      }
      break;
    case CT_FUNC:
      ctr->needsp = 1;
      if (ptrto) { ptrto = 0; ctype_prepc(ctr, '('); ctype_appc(ctr, ')'); }
      ctype_appc(ctr, '(');
      ctype_appc(ctr, ')');
      break;
    default:
      lua_assert(0);
      break;
    }
    ct = ctype_get(ctr->cts, ctype_cid(info));
  }
}