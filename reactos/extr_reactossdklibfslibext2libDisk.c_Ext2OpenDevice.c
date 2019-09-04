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
struct TYPE_6__ {int /*<<< orphan*/  Status; } ;
struct TYPE_5__ {int /*<<< orphan*/  MediaHandle; } ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  TYPE_1__* PEXT2_FILESYS ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_2__ IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  FILE_SYNCHRONOUS_IO_NONALERT ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCreateFile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int SYNCHRONIZE ; 

NTSTATUS
Ext2OpenDevice(  PEXT2_FILESYS Ext2Sys,
                 PUNICODE_STRING DeviceName )
{
    NTSTATUS Status;
    OBJECT_ATTRIBUTES ObjectAttributes;
    HANDLE FileHandle;
    IO_STATUS_BLOCK Iosb;

    //
    // Setup the name in an object attributes structure.
    // Note that we create a name that is case INsensitive
    //
    InitializeObjectAttributes(&ObjectAttributes,           // ptr to structure
                               DeviceName,                  // ptr to file spec
                               OBJ_CASE_INSENSITIVE,        // attributes
                               NULL,                        // root directory handle
                               NULL );                      // ptr to security descriptor

    //
    // Do the create.  In this particular case, we'll have the I/O Manager
    // make our write requests syncrhonous for our convenience.
    //
    Status = NtCreateFile(&FileHandle,                      // returned file handle
                          (GENERIC_READ | GENERIC_WRITE | SYNCHRONIZE),    // desired access
                          &ObjectAttributes,                // ptr to object attributes
                          &Iosb,                            // ptr to I/O status block
                          0,                                // allocation size
                          FILE_ATTRIBUTE_NORMAL,            // file attributes
                          FILE_SHARE_WRITE | FILE_SHARE_READ, // share access
                          FILE_OPEN  /*FILE_SUPERSEDE*/,    // create disposition
                          FILE_SYNCHRONOUS_IO_NONALERT, // create options
                          NULL,                             // ptr to extended attributes
                          0);                               // length of ea buffer

    //
    // Check the system service status
    //
    if( !NT_SUCCESS(Status) )
    {
        DPRINT1("Mke2fs: Create system service failed status = 0x%lx\n", Status);
        return Status;
    }


    //
    // Check the returned status too...
    //
    if(!NT_SUCCESS(Iosb.Status) )
    {
        DPRINT1("Mke2fs: Create failed with status = 0x%lx\n",Iosb.Status);
        return Status;
    }

    Ext2Sys->MediaHandle = FileHandle;

    return Status;
}