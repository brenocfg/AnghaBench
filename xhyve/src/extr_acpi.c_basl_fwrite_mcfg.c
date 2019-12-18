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
 int /*<<< orphan*/  pci_ecfg_base () ; 

__attribute__((used)) static int
basl_fwrite_mcfg(FILE *fp)
{
	int err = 0;

	EFPRINTF(fp, "/*\n");
	EFPRINTF(fp, " * bhyve MCFG template\n");
	EFPRINTF(fp, " */\n");
	EFPRINTF(fp, "[0004]\t\tSignature : \"MCFG\"\n");
	EFPRINTF(fp, "[0004]\t\tTable Length : 00000000\n");
	EFPRINTF(fp, "[0001]\t\tRevision : 01\n");
	EFPRINTF(fp, "[0001]\t\tChecksum : 00\n");
	EFPRINTF(fp, "[0006]\t\tOem ID : \"BHYVE \"\n");
	EFPRINTF(fp, "[0008]\t\tOem Table ID : \"BVMCFG  \"\n");
	EFPRINTF(fp, "[0004]\t\tOem Revision : 00000001\n");

	/* iasl will fill in the compiler ID/revision fields */
	EFPRINTF(fp, "[0004]\t\tAsl Compiler ID : \"xxxx\"\n");
	EFPRINTF(fp, "[0004]\t\tAsl Compiler Revision : 00000000\n");
	EFPRINTF(fp, "[0008]\t\tReserved : 0\n");
	EFPRINTF(fp, "\n");

	EFPRINTF(fp, "[0008]\t\tBase Address : %016llx\n", pci_ecfg_base());
	EFPRINTF(fp, "[0002]\t\tSegment Group: 0000\n");
	EFPRINTF(fp, "[0001]\t\tStart Bus: 00\n");
	EFPRINTF(fp, "[0001]\t\tEnd Bus: FF\n");
	EFPRINTF(fp, "[0004]\t\tReserved : 0\n");
	EFFLUSH(fp);
	return (0);
err_exit:
	return (errno);
}