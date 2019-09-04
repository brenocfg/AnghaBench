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
typedef  int /*<<< orphan*/  attr ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int QuadPart; } ;
struct TYPE_5__ {int Length; int Attributes; int /*<<< orphan*/ * SecurityQualityOfService; int /*<<< orphan*/ * SecurityDescriptor; int /*<<< orphan*/ * ObjectName; scalar_t__ RootDirectory; } ;
typedef  int /*<<< orphan*/  PHANDLE ;
typedef  TYPE_1__ OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;

/* Variables and functions */
 int FILE_READ_ATTRIBUTES ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  pNtCreateNamedPipeFile (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  pRtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testpipe_nt ; 

__attribute__((used)) static NTSTATUS create_pipe(PHANDLE handle, ULONG sharing, ULONG options)
{
    IO_STATUS_BLOCK iosb;
    OBJECT_ATTRIBUTES attr;
    UNICODE_STRING name;
    LARGE_INTEGER timeout;
    NTSTATUS res;

    pRtlInitUnicodeString(&name, testpipe_nt);

    attr.Length                   = sizeof(attr);
    attr.RootDirectory            = 0;
    attr.ObjectName               = &name;
    attr.Attributes               = 0x40; /*case insensitive */
    attr.SecurityDescriptor       = NULL;
    attr.SecurityQualityOfService = NULL;

    timeout.QuadPart = -100000000;

    res = pNtCreateNamedPipeFile(handle, FILE_READ_ATTRIBUTES | SYNCHRONIZE, &attr, &iosb, sharing,  2 /*FILE_CREATE*/,
                                 options, 1, 0, 0, 0xFFFFFFFF, 500, 500, &timeout);
    return res;
}