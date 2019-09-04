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
struct TYPE_3__ {int /*<<< orphan*/ * k; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ Proto ;

/* Variables and functions */
 char* LUA_INTEGER_FMT ; 
 char* LUA_NUMBER_FMT ; 
#define  LUA_TBOOLEAN 133 
#define  LUA_TLNGSTR 132 
#define  LUA_TNIL 131 
#define  LUA_TNUMFLT 130 
#define  LUA_TNUMINT 129 
#define  LUA_TSHRSTR 128 
 int /*<<< orphan*/  PrintString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fltvalue (int /*<<< orphan*/  const*) ; 
 int ivalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 size_t strspn (char*,char*) ; 
 int /*<<< orphan*/  tsvalue (int /*<<< orphan*/  const*) ; 
 int ttype (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void PrintConstant(const Proto* f, int i)
{
 const TValue* o=&f->k[i];
 switch (ttype(o))
 {
  case LUA_TNIL:
	printf("nil");
	break;
  case LUA_TBOOLEAN:
	printf(bvalue(o) ? "true" : "false");
	break;
  case LUA_TNUMFLT:
	{
	char buff[100];
	sprintf(buff,LUA_NUMBER_FMT,fltvalue(o));
	printf("%s",buff);
	if (buff[strspn(buff,"-0123456789")]=='\0') printf(".0");
	break;
	}
  case LUA_TNUMINT:
	printf(LUA_INTEGER_FMT,ivalue(o));
	break;
  case LUA_TSHRSTR: case LUA_TLNGSTR:
	PrintString(tsvalue(o));
	break;
  default:				/* cannot happen */
	printf("? type=%d",ttype(o));
	break;
 }
}