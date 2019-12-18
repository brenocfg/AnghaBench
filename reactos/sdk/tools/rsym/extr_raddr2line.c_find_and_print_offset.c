#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t Address; size_t FileOffset; size_t FunctionOffset; scalar_t__ SourceLine; } ;
struct TYPE_3__ {int SymbolsOffset; int StringsOffset; int SymbolsLength; } ;
typedef  int /*<<< orphan*/  ROSSYM_ENTRY ;
typedef  TYPE_1__* PSYMBOLFILE_HEADER ;
typedef  TYPE_2__* PROSSYM_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,unsigned int,char*) ; 

int
find_and_print_offset (
	void* data,
	size_t offset )
{
	PSYMBOLFILE_HEADER RosSymHeader = (PSYMBOLFILE_HEADER)data;
	PROSSYM_ENTRY Entries = (PROSSYM_ENTRY)((char*)data + RosSymHeader->SymbolsOffset);
	char* Strings = (char*)data + RosSymHeader->StringsOffset;
	size_t symbols = RosSymHeader->SymbolsLength / sizeof(ROSSYM_ENTRY);
	size_t i;

	//if ( RosSymHeader->SymbolsOffset )

	for ( i = 0; i < symbols; i++ )
	{
		if ( Entries[i].Address > offset )
		{
			if ( !i-- )
				return 1;
			else
			{
				PROSSYM_ENTRY e = &Entries[i];
				printf ( "%s:%u (%s)\n",
					&Strings[e->FileOffset],
					(unsigned int)e->SourceLine,
					&Strings[e->FunctionOffset] );
				return 0;
			}
		}
	}
	return 1;
}