#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int magic1; int magic2; int posguid; int lcid; int lcid2; int varflags; int helpstring; int NameOffset; int helpfile; int CustomDataOffset; int res44; int res48; int dispatchpos; scalar_t__ nimpinfos; scalar_t__ nametablechars; scalar_t__ nametablecount; scalar_t__ helpcontext; scalar_t__ helpstringcontext; scalar_t__ nrtypeinfos; scalar_t__ flags; scalar_t__ version; } ;
struct TYPE_5__ {TYPE_1__ typelib_header; } ;
typedef  TYPE_2__ msft_typelib_t ;

/* Variables and functions */

__attribute__((used)) static void ctl2_init_header(
	msft_typelib_t *typelib) /* [I] The typelib to initialize. */
{
    typelib->typelib_header.magic1 = 0x5446534d;
    typelib->typelib_header.magic2 = 0x00010002;
    typelib->typelib_header.posguid = -1;
    typelib->typelib_header.lcid = 0x0409;
    typelib->typelib_header.lcid2 = 0x0;
    typelib->typelib_header.varflags = 0x40;
    typelib->typelib_header.version = 0;
    typelib->typelib_header.flags = 0;
    typelib->typelib_header.nrtypeinfos = 0;
    typelib->typelib_header.helpstring = -1;
    typelib->typelib_header.helpstringcontext = 0;
    typelib->typelib_header.helpcontext = 0;
    typelib->typelib_header.nametablecount = 0;
    typelib->typelib_header.nametablechars = 0;
    typelib->typelib_header.NameOffset = -1;
    typelib->typelib_header.helpfile = -1;
    typelib->typelib_header.CustomDataOffset = -1;
    typelib->typelib_header.res44 = 0x20;
    typelib->typelib_header.res48 = 0x80;
    typelib->typelib_header.dispatchpos = -1;
    typelib->typelib_header.nimpinfos = 0;
}