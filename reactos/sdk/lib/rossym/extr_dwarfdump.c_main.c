#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_10__ {int /*<<< orphan*/  lowpc; int /*<<< orphan*/  ranges; int /*<<< orphan*/  location; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_9__ {int /*<<< orphan*/  c; TYPE_1__ b; } ;
struct TYPE_11__ {int tag; int lowpc; int highpc; TYPE_3__ have; int /*<<< orphan*/  ranges; TYPE_2__ location; int /*<<< orphan*/  name; int /*<<< orphan*/  isexternal; } ;
struct TYPE_12__ {TYPE_4__ attrs; } ;
typedef  char Pe ;
typedef  TYPE_5__ DwarfSym ;
typedef  char Dwarf ;

/* Variables and functions */
#define  TBlock 134 
#define  TConstant 133 
#define  TagCompileUnit 132 
#define  TagConstant 131 
#define  TagFormalParameter 130 
#define  TagSubprogram 129 
#define  TagVariable 128 
 scalar_t__ dwarfenum (char*,TYPE_5__*) ; 
 int dwarfnextsym (char*,TYPE_5__*) ; 
 char* dwarfopen (char*) ; 
 int /*<<< orphan*/  dwarfpctoline (char*,int,char**,char**,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encodefmt ; 
 int /*<<< orphan*/  exits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprfmt ; 
 int /*<<< orphan*/  fmtinstall (char,int /*<<< orphan*/ ) ; 
 char* nil ; 
 char* peopen (char*) ; 
 int /*<<< orphan*/  print (char*,...) ; 
 int /*<<< orphan*/  printrules (char*,int) ; 
 int /*<<< orphan*/  sysfatal (char*,...) ; 
 int /*<<< orphan*/  usage () ; 

void
main(int argc, char **argv)
{
	int c;
	Pe *pe;
	Dwarf *d;
	DwarfSym s;
	char *cdir, *dir, *file;
	ulong line, mtime, length;

	if(argc != 2)
		usage();

#if 0
	fmtinstall('R', exprfmt);
	fmtinstall('H', encodefmt);
#endif

	if((pe = peopen(argv[1])) == nil)
		sysfatal("elfopen %s: %r", argv[1]);
	if((d=dwarfopen(pe)) == nil)
		sysfatal("dwarfopen: %r");

	if(dwarfenum(d, &s) < 0)
		sysfatal("dwarfenumall: %r");

	while(dwarfnextsym(d, &s) == 1){
		switch(s.attrs.tag){
		case TagCompileUnit:
			print("compileunit %s\n", s.attrs.name);
			break;
		case TagSubprogram:
			c = 't';
			goto sym;
		case TagVariable:
			c = 'd';
			goto sym;
		case TagConstant:
			c = 'c';
			goto sym;
		case TagFormalParameter:
			if(!s.attrs.name)
				break;
			c = 'p';
		sym:
			if(s.attrs.isexternal)
				c += 'A' - 'a';
			print("%c %s", c, s.attrs.name);
			if(s.attrs.have.lowpc)
				print(" 0x%lux-0x%lux", s.attrs.lowpc, s.attrs.highpc);
			switch(s.attrs.have.location){
			case TBlock:
				print(" @ %.*H", s.attrs.location.b.len, s.attrs.location.b.data);
				break;
			case TConstant:
				print(" @ 0x%lux", s.attrs.location.c);
				break;
			}
			if(s.attrs.have.ranges)
				print(" ranges@0x%lux", s.attrs.ranges);
			print("\n");
			if(s.attrs.have.lowpc){
				if(dwarfpctoline(d, s.attrs.lowpc, &cdir, &dir, &file, &line, &mtime, &length) < 0)
					print("\tcould not find source: %r\n");
				else if(dir == nil)
					print("\t%s/%s:%lud mtime=%lud length=%lud\n",
						cdir, file, line, mtime, length);
				else
					print("\t%s/%s/%s:%lud mtime=%lud length=%lud\n",
						cdir, dir, file, line, mtime, length);

				if(0) printrules(d, s.attrs.lowpc);
				if(0) printrules(d, (s.attrs.lowpc+s.attrs.highpc)/2);
			}
			break;
		}
	}
	exits(0);
}