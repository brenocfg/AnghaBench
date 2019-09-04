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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EFFLUSH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EFPRINTF (int /*<<< orphan*/ *,char*,...) ; 
 int errno ; 
 int /*<<< orphan*/  hpet_capabilities ; 

__attribute__((used)) static int
basl_fwrite_hpet(FILE *fp)
{
	int err;

	err = 0;

	EFPRINTF(fp, "/*\n");
	EFPRINTF(fp, " * bhyve HPET template\n");
	EFPRINTF(fp, " */\n");
	EFPRINTF(fp, "[0004]\t\tSignature : \"HPET\"\n");
	EFPRINTF(fp, "[0004]\t\tTable Length : 00000000\n");
	EFPRINTF(fp, "[0001]\t\tRevision : 01\n");
	EFPRINTF(fp, "[0001]\t\tChecksum : 00\n");
	EFPRINTF(fp, "[0006]\t\tOem ID : \"BHYVE \"\n");
	EFPRINTF(fp, "[0008]\t\tOem Table ID : \"BVHPET  \"\n");
	EFPRINTF(fp, "[0004]\t\tOem Revision : 00000001\n");

	/* iasl will fill in the compiler ID/revision fields */
	EFPRINTF(fp, "[0004]\t\tAsl Compiler ID : \"xxxx\"\n");
	EFPRINTF(fp, "[0004]\t\tAsl Compiler Revision : 00000000\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp, "[0004]\t\tTimer Block ID : %08X\n", hpet_capabilities);
	EFPRINTF(fp,
	    "[0012]\t\tTimer Block Register : [Generic Address Structure]\n");
	EFPRINTF(fp, "[0001]\t\tSpace ID : 00 [SystemMemory]\n");
	EFPRINTF(fp, "[0001]\t\tBit Width : 00\n");
	EFPRINTF(fp, "[0001]\t\tBit Offset : 00\n");
	EFPRINTF(fp,
		 "[0001]\t\tEncoded Access Width : 00 [Undefined/Legacy]\n");
	EFPRINTF(fp, "[0008]\t\tAddress : 00000000FED00000\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp, "[0001]\t\tHPET Number : 00\n");
	EFPRINTF(fp, "[0002]\t\tMinimum Clock Ticks : 0000\n");
	EFPRINTF(fp, "[0004]\t\tFlags (decoded below) : 00000001\n");
	EFPRINTF(fp, "\t\t\t4K Page Protect : 1\n");
	EFPRINTF(fp, "\t\t\t64K Page Protect : 0\n");
	EFPRINTF(fp, "\n");

	EFFLUSH(fp);

	return (0);

err_exit:
	return (errno);
}