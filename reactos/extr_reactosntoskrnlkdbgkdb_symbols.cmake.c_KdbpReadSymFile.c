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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {int /*<<< orphan*/  FileOffset; int /*<<< orphan*/  FileObject; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PROSSYM_KM_OWN_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MiSimpleRead (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN
KdbpReadSymFile(PVOID FileContext, PVOID Buffer, ULONG Length)
{
    PROSSYM_KM_OWN_CONTEXT Context = (PROSSYM_KM_OWN_CONTEXT)FileContext;
    IO_STATUS_BLOCK Iosb;
    NTSTATUS Status = MiSimpleRead
        (Context->FileObject,
         &Context->FileOffset,
         Buffer,
         Length,
         FALSE,
         &Iosb);
    return NT_SUCCESS(Status);
}