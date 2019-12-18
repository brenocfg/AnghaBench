#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_17__ {struct TYPE_17__* next; int /*<<< orphan*/  name; scalar_t__ EntryPoint; int /*<<< orphan*/  BaseAddress; int /*<<< orphan*/  size; } ;
struct TYPE_12__ {scalar_t__ Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_11__ {int /*<<< orphan*/  Buffer; } ;
struct TYPE_16__ {TYPE_2__ BaseDllName; scalar_t__ EntryPoint; int /*<<< orphan*/  BaseAddress; int /*<<< orphan*/  SizeOfImage; TYPE_1__ FullDllName; } ;
struct TYPE_15__ {struct TYPE_15__* Flink; } ;
struct TYPE_14__ {TYPE_3__* Ldr; } ;
struct TYPE_13__ {TYPE_5__ InLoadOrderModuleList; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_3__* PPEB_LDR_DATA ;
typedef  TYPE_4__* PPEB ;
typedef  TYPE_5__* PLIST_ENTRY ;
typedef  TYPE_6__* PLDR_DATA_TABLE_ENTRY ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_6__* CONTAINING_RECORD (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DEBUG_MODULE_NAME_LEN ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  InLoadOrderModuleList ; 
 int IsAddressValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDR_DATA_TABLE_ENTRY ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  PICE_wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_7__* pdebug_module_tail ; 

BOOLEAN ListUserModules( PPEB peb )
{
	PLIST_ENTRY UserModuleListHead;
	PLIST_ENTRY Entry;
	PLDR_DATA_TABLE_ENTRY Module;
	PPEB_LDR_DATA Ldr;

	ENTER_FUNC();

	Ldr = peb->Ldr;
	if( Ldr && IsAddressValid((ULONG)Ldr)){
		UserModuleListHead = &Ldr->InLoadOrderModuleList;
		ASSERT(IsAddressValid((ULONG)UserModuleListHead));
		Entry = UserModuleListHead->Flink;
		while (Entry != UserModuleListHead)
		{
			Module = CONTAINING_RECORD(Entry, LDR_DATA_TABLE_ENTRY, InLoadOrderModuleList);
			//DbgPrint("Module: %x, BaseAddress: %x\n", Module, Module->BaseAddress);

			DPRINT((0,"FullName: %S, BaseName: %S, Length: %ld, EntryPoint: %x, BaseAddress: %x\n", Module->FullDllName.Buffer,
					Module->BaseDllName.Buffer, Module->SizeOfImage, Module->EntryPoint, Module->BaseAddress ));

			pdebug_module_tail->size = Module->SizeOfImage;
			pdebug_module_tail->BaseAddress = Module->BaseAddress;
			pdebug_module_tail->EntryPoint = (PVOID)(Module->EntryPoint);
			ASSERT(Module->BaseDllName.Length<DEBUG_MODULE_NAME_LEN); //name length is limited
			PICE_wcscpy( pdebug_module_tail->name, Module->BaseDllName.Buffer );
			pdebug_module_tail = pdebug_module_tail->next;

			Entry = Entry->Flink;
		}
	}
	LEAVE_FUNC();
	return TRUE;
}