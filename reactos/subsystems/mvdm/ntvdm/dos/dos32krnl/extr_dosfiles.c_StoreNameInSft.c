#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/ * FileName; } ;
typedef  int /*<<< orphan*/  ShortPath ;
typedef  TYPE_1__* PDOS_FILE_DESCRIPTOR ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetShortPathNameA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _strupr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strrchr (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static VOID StoreNameInSft(LPCSTR FilePath, PDOS_FILE_DESCRIPTOR Descriptor)
{
    CHAR ShortPath[MAX_PATH];
    PCHAR Name;
    PCHAR Extension;

    /* Try to get the short path */
    if (!GetShortPathNameA(FilePath, ShortPath, sizeof(ShortPath)))
    {
        /* If it failed, just use the uppercase long path */
        strncpy(ShortPath, FilePath, sizeof(ShortPath) - 1);
        _strupr(ShortPath);
    }

    /* Get the name part */
    Name = strrchr(ShortPath, '\\');
    if (Name == NULL) Name = ShortPath;

    /* Find the extension */
    Extension = strchr(Name, '.');

    if (Extension)
    {
        /* Terminate the name string, and move the pointer to after the dot */
        *Extension++ = 0;
    }

    /* Copy the name into the SFT descriptor */
    RtlCopyMemory(Descriptor->FileName, Name, min(strlen(Name), 8));

    if (Extension)
    {
        /* Copy the extension too */
        RtlCopyMemory(&Descriptor->FileName[8], Extension, min(strlen(Extension), 3));
    }
}