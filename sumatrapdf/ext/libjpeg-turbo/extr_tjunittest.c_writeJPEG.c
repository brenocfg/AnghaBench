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
 int /*<<< orphan*/  bailout () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fwrite (unsigned char*,unsigned long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void writeJPEG(unsigned char *jpegBuf, unsigned long jpegSize, char *filename)
{
	FILE *file=fopen(filename, "wb");
	if(!file || fwrite(jpegBuf, jpegSize, 1, file)!=1)
	{
		printf("ERROR: Could not write to %s.\n%s\n", filename, strerror(errno));
		bailout();
	}

	bailout:
	if(file) fclose(file);
}