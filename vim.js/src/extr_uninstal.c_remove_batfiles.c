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
struct TYPE_2__ {int /*<<< orphan*/  batname; } ;

/* Variables and functions */
 int TARGET_COUNT ; 
 scalar_t__ batfile_thisversion (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  remove (char*) ; 
 char* searchpath_save (int /*<<< orphan*/ ) ; 
 TYPE_1__* targets ; 

__attribute__((used)) static int
remove_batfiles(int doit)
{
    char *batfile_path;
    int	 i;
    int	 found = 0;

    for (i = 1; i < TARGET_COUNT; ++i)
    {
	batfile_path = searchpath_save(targets[i].batname);
	if (batfile_path != NULL && batfile_thisversion(batfile_path))
	{
	    ++found;
	    if (doit)
	    {
		printf("removing %s\n", batfile_path);
		remove(batfile_path);
	    }
	    else
		printf(" - the batch file %s\n", batfile_path);
	    free(batfile_path);
	}
    }
    return found;
}