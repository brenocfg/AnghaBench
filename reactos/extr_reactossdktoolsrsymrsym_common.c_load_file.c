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
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 void* malloc (size_t) ; 

void*
load_file ( const char* file_name, size_t* file_size )
{
	FILE* f;
	void* FileData = NULL;

	f = fopen ( file_name, "rb" );
	if (f != NULL)
	{
		fseek(f, 0L, SEEK_END);
		*file_size = ftell(f);
		fseek(f, 0L, SEEK_SET);
		FileData = malloc(*file_size);
		if (FileData != NULL)
		{
			if ( *file_size != fread(FileData, 1, *file_size, f) )
			{
				free(FileData);
				FileData = NULL;
			}
		}
		fclose(f);
	}
	return FileData;
}