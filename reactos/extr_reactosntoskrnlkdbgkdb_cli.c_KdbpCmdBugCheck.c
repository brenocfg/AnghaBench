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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KdbpBugCheckRequested ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
KdbpCmdBugCheck(
    ULONG Argc,
    PCHAR Argv[])
{
    /* Set the flag and quit looping */
    KdbpBugCheckRequested = TRUE;

    return FALSE;
}