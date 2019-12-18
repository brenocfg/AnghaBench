#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ Length; } ;
struct TYPE_13__ {scalar_t__ Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_12__ {int nsections; TYPE_1__* sect; scalar_t__ imagebase; } ;
struct TYPE_11__ {int /*<<< orphan*/  SizeOfRawData; scalar_t__ VirtualAddress; } ;
typedef  TYPE_1__ PeSect ;
typedef  TYPE_2__ Pe ;
typedef  scalar_t__ PCHAR ;
typedef  TYPE_3__* PANSI_STRING ;
typedef  TYPE_4__ ANSI_STRING ;

/* Variables and functions */
 TYPE_3__* ANSI_NAME_STRING (TYPE_1__*) ; 
 int /*<<< orphan*/  DPRINT (char*,char const*,...) ; 
 int /*<<< orphan*/  RtlInitAnsiString (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 TYPE_1__* nil ; 

PeSect *pesection(Pe *pe, const char *name) 
{
	int i;
	ANSI_STRING WantName;
	RtlInitAnsiString(&WantName, name);
	DPRINT("Searching for section %s\n", name);
	for (i = 0; i < pe->nsections; i++) {
		PANSI_STRING AnsiString = ANSI_NAME_STRING(&pe->sect[i]);
		if (WantName.Length == AnsiString->Length &&
			!memcmp(AnsiString->Buffer, name, WantName.Length)) {
			DPRINT("Found %s (%d) @ %x (%x)\n", name, i, 
				   ((PCHAR)pe->imagebase)+pe->sect[i].VirtualAddress,
				   pe->sect[i].SizeOfRawData);
			return &pe->sect[i];
		}
	}
	DPRINT("%s not found\n", name);
	return nil;
}