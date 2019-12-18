#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct assembly_identity {int /*<<< orphan*/  public_key; int /*<<< orphan*/  name; int /*<<< orphan*/  arch; } ;
struct actctx_loader {int dummy; } ;
typedef  int /*<<< orphan*/  manifest_dirW ;
typedef  int /*<<< orphan*/  attr ;
typedef  char WCHAR ;
struct TYPE_11__ {int Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_14__ {char* NtSystemRoot; } ;
struct TYPE_13__ {int /*<<< orphan*/  Status; } ;
struct TYPE_12__ {int Length; int /*<<< orphan*/ * SecurityQualityOfService; int /*<<< orphan*/ * SecurityDescriptor; TYPE_1__* ObjectName; int /*<<< orphan*/  Attributes; scalar_t__ RootDirectory; } ;
typedef  TYPE_2__ OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_3__ IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int FILE_DIRECTORY_FILE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int FILE_SYNCHRONOUS_IO_NONALERT ; 
 int GENERIC_READ ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtOpenFile (int /*<<< orphan*/ *,int,TYPE_2__*,TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 char* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlDosPathNameToNtPathName_U (char*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,char*) ; 
 char* RtlReAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_NO_SUCH_FILE ; 
 int SYNCHRONIZE ; 
 TYPE_5__* SharedUserData ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_manifest_in_manifest_file (struct actctx_loader*,struct assembly_identity*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* lookup_manifest_file (int /*<<< orphan*/ ,struct assembly_identity*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  open_nt_file (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  strcpyW (char*,char*) ; 
 int strlenW (char*) ; 
 scalar_t__* strrchrW (char*,char) ; 

__attribute__((used)) static NTSTATUS lookup_winsxs(struct actctx_loader* acl, struct assembly_identity* ai)
{
    struct assembly_identity    sxs_ai;
    UNICODE_STRING              path_us;
    OBJECT_ATTRIBUTES           attr;
    IO_STATUS_BLOCK             io;
    WCHAR *path, *file = NULL;
    HANDLE handle;

    static const WCHAR manifest_dirW[] =
        {'\\','w','i','n','s','x','s','\\','m','a','n','i','f','e','s','t','s',0};

    if (!ai->arch || !ai->name || !ai->public_key) return STATUS_NO_SUCH_FILE;

    if (!(path = RtlAllocateHeap( RtlGetProcessHeap(), 0,
                                  ((strlenW(SharedUserData->NtSystemRoot) + 1) *sizeof(WCHAR)) + sizeof(manifest_dirW) )))
        return STATUS_NO_MEMORY;

    memcpy( path, SharedUserData->NtSystemRoot, strlenW(SharedUserData->NtSystemRoot) * sizeof(WCHAR) );
    memcpy( path + strlenW(SharedUserData->NtSystemRoot), manifest_dirW, sizeof(manifest_dirW) );

    if (!RtlDosPathNameToNtPathName_U( path, &path_us, NULL, NULL ))
    {
        RtlFreeHeap( RtlGetProcessHeap(), 0, path );
        return STATUS_NO_SUCH_FILE;
    }
    RtlFreeHeap( RtlGetProcessHeap(), 0, path );

    attr.Length = sizeof(attr);
    attr.RootDirectory = 0;
    attr.Attributes = OBJ_CASE_INSENSITIVE;
    attr.ObjectName = &path_us;
    attr.SecurityDescriptor = NULL;
    attr.SecurityQualityOfService = NULL;

    if (!NtOpenFile( &handle, GENERIC_READ | SYNCHRONIZE, &attr, &io, FILE_SHARE_READ | FILE_SHARE_WRITE,
                     FILE_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT ))
    {
        sxs_ai = *ai;
        file = lookup_manifest_file( handle, &sxs_ai );
        NtClose( handle );
    }
    if (!file)
    {
        RtlFreeUnicodeString( &path_us );
        return STATUS_NO_SUCH_FILE;
    }

    /* append file name to directory path */
    if (!(path = RtlReAllocateHeap( RtlGetProcessHeap(), 0, path_us.Buffer,
                                    path_us.Length + (strlenW(file) + 2) * sizeof(WCHAR) )))
    {
        RtlFreeHeap( RtlGetProcessHeap(), 0, file );
        RtlFreeUnicodeString( &path_us );
        return STATUS_NO_MEMORY;
    }

    path[path_us.Length/sizeof(WCHAR)] = '\\';
    strcpyW( path + path_us.Length/sizeof(WCHAR) + 1, file );
    RtlInitUnicodeString( &path_us, path );
    *strrchrW(file, '.') = 0;  /* remove .manifest extension */

    if (!open_nt_file( &handle, &path_us ))
    {
        io.Status = get_manifest_in_manifest_file(acl, &sxs_ai, path_us.Buffer, file, TRUE, handle);
        NtClose( handle );
    }
    else io.Status = STATUS_NO_SUCH_FILE;

    RtlFreeHeap( RtlGetProcessHeap(), 0, file );
    RtlFreeUnicodeString( &path_us );
    return io.Status;
}