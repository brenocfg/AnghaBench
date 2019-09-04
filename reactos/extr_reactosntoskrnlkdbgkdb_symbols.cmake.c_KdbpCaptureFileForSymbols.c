#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ QuadPart; } ;
struct TYPE_6__ {int /*<<< orphan*/  FileObject; TYPE_1__ FileOffset; } ;
typedef  TYPE_2__* PROSSYM_KM_OWN_CONTEXT ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;

/* Variables and functions */
 TYPE_2__* ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  ObReferenceObject (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PROSSYM_KM_OWN_CONTEXT
KdbpCaptureFileForSymbols(PFILE_OBJECT FileObject)
{
    PROSSYM_KM_OWN_CONTEXT Context = ExAllocatePool(NonPagedPool, sizeof(*Context));
    if (!Context) return NULL;
    ObReferenceObject(FileObject);
    Context->FileOffset.QuadPart = 0;
    Context->FileObject = FileObject;
    return Context;
}