#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sizecode; int /*<<< orphan*/ * p; scalar_t__* code; } ;
typedef  TYPE_1__ Proto ;
typedef  size_t OpCode ;
typedef  scalar_t__ Instruction ;

/* Variables and functions */
 int GETARG_A (scalar_t__) ; 
 int GETARG_Ax (scalar_t__) ; 
 int GETARG_B (scalar_t__) ; 
 int GETARG_Bx (scalar_t__) ; 
 int GETARG_C (scalar_t__) ; 
 int GETARG_sBx (scalar_t__) ; 
 size_t GET_OPCODE (scalar_t__) ; 
 int INDEXK (int) ; 
 int /*<<< orphan*/  ISK (int) ; 
 int MYK (int) ; 
#define  OP_ADD 160 
#define  OP_BAND 159 
#define  OP_BOR 158 
#define  OP_BXOR 157 
#define  OP_CLOSURE 156 
#define  OP_DIV 155 
#define  OP_EQ 154 
#define  OP_EXTRAARG 153 
#define  OP_FORLOOP 152 
#define  OP_FORPREP 151 
#define  OP_GETTABLE 150 
#define  OP_GETTABUP 149 
#define  OP_GETUPVAL 148 
#define  OP_IDIV 147 
#define  OP_JMP 146 
#define  OP_LE 145 
#define  OP_LOADK 144 
#define  OP_LT 143 
#define  OP_MUL 142 
#define  OP_POW 141 
#define  OP_SELF 140 
#define  OP_SETLIST 139 
#define  OP_SETTABLE 138 
#define  OP_SETTABUP 137 
#define  OP_SETUPVAL 136 
#define  OP_SHL 135 
#define  OP_SHR 134 
#define  OP_SUB 133 
#define  OP_TFORLOOP 132 
 int /*<<< orphan*/  OpArgK ; 
 int /*<<< orphan*/  OpArgN ; 
 int /*<<< orphan*/  OpArgU ; 
 int /*<<< orphan*/  PrintConstant (TYPE_1__ const*,int) ; 
 char* UPVALNAME (int) ; 
 int /*<<< orphan*/  VOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getBMode (size_t) ; 
 int /*<<< orphan*/  getCMode (size_t) ; 
 int getOpMode (size_t) ; 
 int getfuncline (TYPE_1__ const*,int) ; 
#define  iABC 131 
#define  iABx 130 
#define  iAsBx 129 
#define  iAx 128 
 char** luaP_opnames ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void PrintCode(const Proto* f)
{
 const Instruction* code=f->code;
 int pc,n=f->sizecode;
 for (pc=0; pc<n; pc++)
 {
  Instruction i=code[pc];
  OpCode o=GET_OPCODE(i);
  int a=GETARG_A(i);
  int b=GETARG_B(i);
  int c=GETARG_C(i);
  int ax=GETARG_Ax(i);
  int bx=GETARG_Bx(i);
  int sbx=GETARG_sBx(i);
  int line=getfuncline(f,pc);
  printf("\t%d\t",pc+1);
  if (line>0) printf("[%d]\t",line); else printf("[-]\t");
  printf("%-9s\t",luaP_opnames[o]);
  switch (getOpMode(o))
  {
   case iABC:
    printf("%d",a);
    if (getBMode(o)!=OpArgN) printf(" %d",ISK(b) ? (MYK(INDEXK(b))) : b);
    if (getCMode(o)!=OpArgN) printf(" %d",ISK(c) ? (MYK(INDEXK(c))) : c);
    break;
   case iABx:
    printf("%d",a);
    if (getBMode(o)==OpArgK) printf(" %d",MYK(bx));
    if (getBMode(o)==OpArgU) printf(" %d",bx);
    break;
   case iAsBx:
    printf("%d %d",a,sbx);
    break;
   case iAx:
    printf("%d",MYK(ax));
    break;
  }
  switch (o)
  {
   case OP_LOADK:
    printf("\t; "); PrintConstant(f,bx);
    break;
   case OP_GETUPVAL:
   case OP_SETUPVAL:
    printf("\t; %s",UPVALNAME(b));
    break;
   case OP_GETTABUP:
    printf("\t; %s",UPVALNAME(b));
    if (ISK(c)) { printf(" "); PrintConstant(f,INDEXK(c)); }
    break;
   case OP_SETTABUP:
    printf("\t; %s",UPVALNAME(a));
    if (ISK(b)) { printf(" "); PrintConstant(f,INDEXK(b)); }
    if (ISK(c)) { printf(" "); PrintConstant(f,INDEXK(c)); }
    break;
   case OP_GETTABLE:
   case OP_SELF:
    if (ISK(c)) { printf("\t; "); PrintConstant(f,INDEXK(c)); }
    break;
   case OP_SETTABLE:
   case OP_ADD:
   case OP_SUB:
   case OP_MUL:
   case OP_POW:
   case OP_DIV:
   case OP_IDIV:
   case OP_BAND:
   case OP_BOR:
   case OP_BXOR:
   case OP_SHL:
   case OP_SHR:
   case OP_EQ:
   case OP_LT:
   case OP_LE:
    if (ISK(b) || ISK(c))
    {
     printf("\t; ");
     if (ISK(b)) PrintConstant(f,INDEXK(b)); else printf("-");
     printf(" ");
     if (ISK(c)) PrintConstant(f,INDEXK(c)); else printf("-");
    }
    break;
   case OP_JMP:
   case OP_FORLOOP:
   case OP_FORPREP:
   case OP_TFORLOOP:
    printf("\t; to %d",sbx+pc+2);
    break;
   case OP_CLOSURE:
    printf("\t; %p",VOID(f->p[bx]));
    break;
   case OP_SETLIST:
    if (c==0) printf("\t; %d",(int)code[++pc]); else printf("\t; %d",c);
    break;
   case OP_EXTRAARG:
    printf("\t; "); PrintConstant(f,ax);
    break;
   default:
    break;
  }
  printf("\n");
 }
}