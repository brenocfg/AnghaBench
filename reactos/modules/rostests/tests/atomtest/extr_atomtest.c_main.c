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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
typedef  int RTL_ATOM ;
typedef  int /*<<< orphan*/ * PRTL_ATOM_TABLE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlAddAtomToAtomTable (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  RtlCreateAtomTable (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RtlDestroyAtomTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlLookupAtomInAtomTable (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  RtlPinAtomInAtomTable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlQueryAtomInAtomTable (int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char* argv[])
{
   PRTL_ATOM_TABLE AtomTable = NULL;
   RTL_ATOM AtomA = -1, AtomB = -1, AtomC = -1;
   NTSTATUS Status;
   WCHAR Buffer[BUFFER_SIZE];
   ULONG NameLength, Data1, Data2;

   printf("Atom table test app\n\n");

   printf("RtlCreateAtomTable()\n");
   Status = RtlCreateAtomTable(37,
			       &AtomTable);
   printf("  Status 0x%08lx\n", Status);

   if (NT_SUCCESS(Status))
     {
	printf("  AtomTable %p\n", AtomTable);

	printf("RtlAddAtomToAtomTable()\n");
	Status = RtlAddAtomToAtomTable(AtomTable,
				       L"TestAtomA",
				       &AtomA);
	printf("  Status 0x%08lx\n", Status);
	if (NT_SUCCESS(Status))
	  {
	     printf("  AtomA 0x%x\n", AtomA);
	  }

	printf("RtlAddAtomToAtomTable()\n");
	Status = RtlAddAtomToAtomTable(AtomTable,
				       L"TestAtomB",
				       &AtomB);
	printf("  Status 0x%08lx\n", Status);
	if (NT_SUCCESS(Status))
	  {
	     printf("  AtomB 0x%x\n", AtomB);
	  }


	printf("RtlLookupAtomInAtomTable()\n");
	Status = RtlLookupAtomInAtomTable(AtomTable,
					  L"TestAtomA",
					  &AtomC);
	printf("  Status 0x%08lx\n", Status);
	if (NT_SUCCESS(Status))
	  {
	     printf("  AtomC 0x%x\n", AtomC);
	  }


	printf("RtlPinAtomInAtomTable()\n");
	Status = RtlPinAtomInAtomTable(AtomTable,
				       AtomC);
	printf("  Status 0x%08lx\n", Status);

	printf("RtlPinAtomInAtomTable()\n");
	Status = RtlPinAtomInAtomTable(AtomTable,
				       AtomC);
	printf("  Status 0x%08lx\n", Status);


//	printf("RtlDeleteAtomFromAtomTable()\n");
//	Status = RtlDeleteAtomFromAtomTable(AtomTable,
//					    AtomC);
//	printf("  Status 0x%08lx\n", Status);


//	printf("RtlEmptyAtomTable()\n");
//	Status = RtlEmptyAtomTable(AtomTable,
//				   TRUE);
//	printf("  Status 0x%08lx\n", Status);


//	printf("RtlLookupAtomInAtomTable()\n");
//	Status = RtlLookupAtomInAtomTable(AtomTable,
//					  L"TestAtomA",
//					  &AtomC);
//	printf("  Status 0x%08lx\n", Status);


	printf("RtlQueryAtomInAtomTable()\n");
	NameLength = sizeof(WCHAR) * BUFFER_SIZE;
	Status = RtlQueryAtomInAtomTable(AtomTable,
					 AtomC,
					 &Data1,
					 &Data2,
					 Buffer,
					 &NameLength);
	printf("  Status 0x%08lx\n", Status);
	if (NT_SUCCESS(Status))
	  {
	     printf("  RefCount %ld\n", Data1);
	     printf("  PinCount %ld\n", Data2);
	     printf("  NameLength %lu\n", NameLength);
	     printf("  AtomName: %S\n", Buffer);
	  }

	printf("RtlDestroyAtomTable()\n");
	RtlDestroyAtomTable(AtomTable);


	printf("Atom table test app finished\n");
     }

   return(0);
}