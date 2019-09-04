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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 scalar_t__ CheckAgainstFAT (int /*<<< orphan*/ *) ; 
 scalar_t__ CheckAgainstMBR (int /*<<< orphan*/ *) ; 
 scalar_t__ CheckAgainstNTFS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DiskFormat ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  FILE_SYNCHRONOUS_IO_NONALERT ; 
 int GENERIC_READ ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtOpenFile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECTOR_SIZE ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int main(int argc, char ** argv)
{
    HANDLE FileHandle;
    NTSTATUS Status;
    OBJECT_ATTRIBUTES ObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;
    WCHAR Buffer[MAX_PATH];
    UNICODE_STRING Name;
    PVOID Sector;

    Sector = malloc(SECTOR_SIZE);
    if (Sector == NULL)
    {
        fprintf(stderr, "Failed allocating memory!\n");
        return 0;
    }

    /* We first open disk */
    swprintf(Buffer, DiskFormat, 0, 0);
    RtlInitUnicodeString(&Name, Buffer);
    InitializeObjectAttributes(&ObjectAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    Status = NtOpenFile(&FileHandle,
                        GENERIC_READ | SYNCHRONIZE,
                        &ObjectAttributes,
                        &IoStatusBlock,
                        0,
                        FILE_SYNCHRONOUS_IO_NONALERT);
    if (!NT_SUCCESS(Status))
    {
        free(Sector);
        fprintf(stderr, "Failed opening disk! %lx\n", Status);
        return 0;
    }

    /* Read first sector of the disk */
    Status = NtReadFile(FileHandle,
                        NULL,
                        NULL,
                        NULL,
                        &IoStatusBlock,
                        Sector,
                        SECTOR_SIZE,
                        NULL,
                        NULL);
    NtClose(FileHandle);
    if (!NT_SUCCESS(Status))
    {
        free(Sector);
        fprintf(stderr, "Failed reading sector 0! %lx\n", Status);
        return 0;
    }

    /* Is it FAT? */
    if (CheckAgainstFAT(Sector))
    {
        printf("Sector 0 seems to be FAT boot sector\n");
    }
    /* Is it NTFS? */
    else if (CheckAgainstNTFS(Sector))
    {
        printf("Sector 0 seems to be NTFS boot sector\n");
    }
    /* Is it MBR? */
    else if (CheckAgainstMBR(Sector))
    {
        printf("Sector 0 might be MBR\n");
    }
    /* We don't support anything else */
    else
    {
        printf("Sector 0 not recognized\n");
    }

    /* Redo it with first partition */
    swprintf(Buffer, DiskFormat, 0, 1);
    RtlInitUnicodeString(&Name, Buffer);
    InitializeObjectAttributes(&ObjectAttributes,
                               &Name,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    Status = NtOpenFile(&FileHandle,
                        GENERIC_READ | SYNCHRONIZE,
                        &ObjectAttributes,
                        &IoStatusBlock,
                        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                        FILE_SYNCHRONOUS_IO_NONALERT);
    if (!NT_SUCCESS(Status))
    {
        free(Sector);
        fprintf(stderr, "Failed opening partition! %lx\n", Status);
        return 0;
    }

    /* Read first sector of the partition */
    Status = NtReadFile(FileHandle,
                        NULL,
                        NULL,
                        NULL,
                        &IoStatusBlock,
                        Sector,
                        SECTOR_SIZE,
                        NULL,
                        NULL);
    if (!NT_SUCCESS(Status))
    {
        free(Sector);
        fprintf(stderr, "Failed reading first sector of the partition! %lx\n", Status);
        return 0;
    }

    /* Is it FAT? */
    if (CheckAgainstFAT(Sector))
    {
        printf("Seems to be a FAT partittion\n");
    }
    /* Is it NTFS? */
    else if (CheckAgainstNTFS(Sector))
    {
        printf("Seems to be a NTFS partition\n");
    }
    /* Is it MBR? */
    else if (CheckAgainstMBR(Sector))
    {
        printf("Seems to be MBR\n");
    }
    /* We don't support anything else */
    else
    {
        printf("Not recognized\n");
    }

    free(Sector);

    return 0;
}