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
typedef  int /*<<< orphan*/  uvlong ;
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  DwarfBuf ;

/* Variables and functions */
#define  FormAddr 140 
#define  FormData1 139 
#define  FormData2 138 
#define  FormData4 137 
#define  FormData8 136 
#define  FormRef1 135 
#define  FormRef2 134 
#define  FormRef4 133 
#define  FormRef8 132 
#define  FormRefAddr 131 
#define  FormRefUdata 130 
#define  FormSdata 129 
#define  FormUdata 128 
 int TAddress ; 
 int TConstant ; 
 int TReference ; 
 int /*<<< orphan*/  dwarfget1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarfget128 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarfget128s (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarfget2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarfget4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarfget8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarfgetaddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  werrstr (char*) ; 

__attribute__((used)) static int
getulong(DwarfBuf *b, int form, ulong unit, ulong *u, int *type)
{
    static int nbad;
    uvlong uv;

    switch(form){
    default:
        return -1;

	/* addresses */
    case FormAddr:
        *type = TAddress;
        *u = dwarfgetaddr(b);
        return 0;

	/* references */
    case FormRefAddr:
        /* absolute ref in .debug_info */
        *type = TReference;
        *u = dwarfgetaddr(b);
        return 0;
    case FormRef1:
        *u = dwarfget1(b);
        goto relativeref;
    case FormRef2:
        *u = dwarfget2(b);
        goto relativeref;
    case FormRef4:
        *u = dwarfget4(b);
        goto relativeref;
    case FormRef8:
        *u = dwarfget8(b);
        goto relativeref;
    case FormRefUdata:
        *u = dwarfget128(b);
    relativeref:
        *u += unit;
        *type = TReference;
        return 0;

	/* constants */
    case FormData1:
        *u = dwarfget1(b);
        goto constant;
    case FormData2:
        *u = dwarfget2(b);
        goto constant;
    case FormData4:
        *u = dwarfget4(b);
        goto constant;
    case FormData8:
        uv = dwarfget8(b);
        *u = uv;
        if(uv != *u && ++nbad == 1)
            werrstr("dwarf: truncating 64-bit attribute constants");
        goto constant;
    case FormSdata:
        *u = dwarfget128s(b);
        goto constant;
    case FormUdata:
        *u = dwarfget128(b);
    constant:
        *type = TConstant;
        return 0;
    }
}