#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_2__ {int n_strx; int /*<<< orphan*/  n_type; int /*<<< orphan*/  n_value; int /*<<< orphan*/  n_desc; int /*<<< orphan*/  n_other; } ;
typedef  int /*<<< orphan*/  STAB_ENTRY ;
typedef  TYPE_1__* PSTAB_ENTRY ;
typedef  int /*<<< orphan*/  PIMAGE_SECTION_HEADER ;
typedef  int /*<<< orphan*/  PIMAGE_FILE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 char* stab_type_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
IterateStabs(ULONG StabSymbolsLength, void *StabSymbolsBase,
             ULONG StabStringsLength, void *StabStringsBase,
             ULONG_PTR ImageBase, PIMAGE_FILE_HEADER PEFileHeader,
             PIMAGE_SECTION_HEADER PESectionHeaders)
{
  PSTAB_ENTRY e;
  ULONG Count, i;

  e = StabSymbolsBase;
  Count = StabSymbolsLength / sizeof(STAB_ENTRY);
  if (Count == 0) /* No symbol info */
    return;

  printf ( "type,other,desc,value,str\n" );
  for (i = 0; i < Count; i++)
    {
	  printf ( "%s,%lu(0x%x),%lu(0x%x),%lu(0x%x),%s\n",
		  stab_type_name(e[i].n_type),
		  e[i].n_other,
		  e[i].n_other,
		  e[i].n_desc,
		  e[i].n_desc,
		  e[i].n_value,
		  e[i].n_value,
		  (char *) StabStringsBase + e[i].n_strx );
    }
}