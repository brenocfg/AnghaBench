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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dumping_on ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fs_file ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ stricmp (char*,char*) ; 
 int /*<<< orphan*/  test_NtGdiDdCanCreateSurface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_NtGdiDdCreateDirectDrawObject () ; 
 int /*<<< orphan*/  test_NtGdiDdDeleteDirectDrawObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_NtGdiDdGetScanLine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_NtGdiDdQueryDirectDrawObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_NtGdiDdWaitForVerticalBlank (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
    HANDLE hDirectDrawLocal;

    if (argc == 2)
    {
        if (stricmp(argv[1],"-dump")==0)
        {
            dumping_on = TRUE;
        }

        if ( (stricmp(argv[1],"-help")==0) ||
             (stricmp(argv[1],"-?")==0) ||
             (stricmp(argv[1],"/help")==0) ||
             (stricmp(argv[1],"/?")==0) )
        {
            printf("the %s support follow param \n",argv[0]);
            printf("-dump              : It dump all data it resvie to screen \n");
            printf("-dumpfile filename : It dump all data it resvie to file \n");
            printf("\nrember u can only use one of them at time \n");
            exit(1);
        }
    }

    if (argc == 3)
    {
        if (stricmp(argv[1],"-dumpfile")==0)
        {
            /* create or over write a file in binary mode, and redirect printf to the file */ 
            if ( (fs_file = freopen(argv[2], "wb", stdout)) != NULL) 
            {
                dumping_on = TRUE;
            }
        }
    }

    hDirectDrawLocal = test_NtGdiDdCreateDirectDrawObject();

    test_NtGdiDdQueryDirectDrawObject(hDirectDrawLocal);

    test_NtGdiDdGetScanLine(hDirectDrawLocal);

    test_NtGdiDdWaitForVerticalBlank(hDirectDrawLocal);

    test_NtGdiDdCanCreateSurface(hDirectDrawLocal);

    test_NtGdiDdDeleteDirectDrawObject(hDirectDrawLocal);

    if (fs_file != NULL)
    {
        fclose(fs_file);
    }
    return 0;
}