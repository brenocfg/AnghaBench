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

/* Variables and functions */
 char* convert_path (char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t my_atoi (char const*) ; 
 int process_file (char*,size_t) ; 
 int /*<<< orphan*/  stderr ; 

int main ( int argc, const char** argv )
{
	char* path;
	size_t offset;
	int res;

	if ( argc != 3 )
	{
		fprintf(stderr, "Usage: raddr2line <exefile> <offset>\n");
		exit(1);
	}

	path = convert_path ( argv[1] );
	offset = my_atoi ( argv[2] );

	res = process_file ( path, offset );

	free ( path );

	return res;
}