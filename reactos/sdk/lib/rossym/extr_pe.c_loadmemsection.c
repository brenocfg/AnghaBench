#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int len; scalar_t__ data; } ;
struct TYPE_10__ {scalar_t__ fd; } ;
struct TYPE_9__ {int VirtualAddress; int SizeOfRawData; } ;
typedef  TYPE_1__ PeSect ;
typedef  TYPE_2__ Pe ;
typedef  char* PCHAR ;
typedef  TYPE_3__ DwarfBlock ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,char*,scalar_t__,int) ; 
 scalar_t__ RosSymAllocMem (int) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,char*,int) ; 
 TYPE_1__* nil ; 
 TYPE_1__* pesection (TYPE_2__*,char*) ; 

int
loadmemsection(Pe *pe, char *name, DwarfBlock *b)
{
	PeSect *s;

	if((s = pesection(pe, name)) == nil)
		return -1;
	DPRINT("Loading section %s (ImageBase %x RVA %x)\n", name, pe->fd, s->VirtualAddress);
	b->data = RosSymAllocMem(s->SizeOfRawData);
	b->len = s->SizeOfRawData;
	PCHAR DataSource = ((char *)pe->fd) + s->VirtualAddress;
	DPRINT("Copying to %x from %x (%x)\n", DataSource, b->data, b->len);
	RtlCopyMemory(b->data, DataSource, s->SizeOfRawData);
	
	return s->SizeOfRawData;
}