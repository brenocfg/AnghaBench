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
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

VOID
PrintUsage()
{
	printf("Syntax:\n\n");
	printf("dumpsym <file> [-sp=<symbolpath>] [-p] [<symname>]\n\n");
	printf("<file>           The PE file you want to dump the symbols of\n");
	printf("-sp=<symbolpath> Path to your symbol files.\n");
	printf("                 Default is MS symbol server.\n");
	printf("-p               Enable struct positions.\n");
	printf("<symname>        A name of a Symbol, you want to dump\n");
	printf("                 Default is all symbols.\n");
	printf("\n");
}