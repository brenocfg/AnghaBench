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
typedef  int /*<<< orphan*/  attr ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_3__ {int Length; int /*<<< orphan*/ * SecurityQualityOfService; int /*<<< orphan*/ * SecurityDescriptor; int /*<<< orphan*/ * ObjectName; int /*<<< orphan*/  Attributes; scalar_t__ RootDirectory; } ;
typedef  TYPE_1__ OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FILE_SYNCHRONOUS_IO_ALERT ; 
 int GENERIC_READ ; 
 int /*<<< orphan*/  NtOpenFile (int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int SYNCHRONIZE ; 

__attribute__((used)) static NTSTATUS open_nt_file( HANDLE *handle, UNICODE_STRING *name )
{
    OBJECT_ATTRIBUTES attr;
    IO_STATUS_BLOCK io;

    attr.Length = sizeof(attr);
    attr.RootDirectory = 0;
    attr.Attributes = OBJ_CASE_INSENSITIVE;
    attr.ObjectName = name;
    attr.SecurityDescriptor = NULL;
    attr.SecurityQualityOfService = NULL;
    return NtOpenFile( handle, GENERIC_READ | SYNCHRONIZE, &attr, &io, FILE_SHARE_READ, FILE_SYNCHRONOUS_IO_ALERT );
}