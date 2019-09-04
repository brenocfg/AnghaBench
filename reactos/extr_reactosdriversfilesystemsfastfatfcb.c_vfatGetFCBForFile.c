#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ USHORT ;
struct TYPE_27__ {int* Buffer; int Length; int MaximumLength; } ;
typedef  TYPE_2__ UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_29__ {int Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_26__ {int Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_28__ {TYPE_1__ LongNameU; TYPE_4__ PathNameU; struct TYPE_28__* parentFcb; } ;
typedef  int* PWCHAR ;
typedef  TYPE_3__* PVFATFCB ;
typedef  TYPE_4__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NameBuffer ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 TYPE_2__ RTL_CONSTANT_STRING (char*) ; 
 int /*<<< orphan*/  RtlAppendUnicodeStringToString (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  RtlAppendUnicodeToString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  RtlCopyMemory (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlCopyUnicodeString (TYPE_2__*,TYPE_4__*) ; 
 scalar_t__ RtlEqualUnicodeString (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlInitEmptyUnicodeString (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlMoveMemory (int*,int*,int) ; 
 scalar_t__ STATUS_OBJECT_NAME_INVALID ; 
 scalar_t__ STATUS_OBJECT_NAME_NOT_FOUND ; 
 scalar_t__ STATUS_OBJECT_PATH_NOT_FOUND ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ vfatDirFindFile (int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__*,TYPE_3__**) ; 
 int /*<<< orphan*/  vfatFCBIsDirectory (TYPE_3__*) ; 
 int /*<<< orphan*/  vfatGrabFCB (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* vfatGrabFCBFromTable (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_3__* vfatOpenRootFCB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfatReleaseFCB (int /*<<< orphan*/ ,TYPE_3__*) ; 

NTSTATUS
vfatGetFCBForFile(
    PDEVICE_EXTENSION pVCB,
    PVFATFCB *pParentFCB,
    PVFATFCB *pFCB,
    PUNICODE_STRING pFileNameU)
{
    NTSTATUS status;
    PVFATFCB FCB = NULL;
    PVFATFCB parentFCB;
    UNICODE_STRING NameU;
    UNICODE_STRING RootNameU = RTL_CONSTANT_STRING(L"\\");
    UNICODE_STRING FileNameU;
    WCHAR NameBuffer[260];
    PWCHAR curr, prev, last;
    ULONG Length;

    DPRINT("vfatGetFCBForFile (%p,%p,%p,%wZ)\n",
           pVCB, pParentFCB, pFCB, pFileNameU);

    RtlInitEmptyUnicodeString(&FileNameU, NameBuffer, sizeof(NameBuffer));

    parentFCB = *pParentFCB;

    if (parentFCB == NULL)
    {
        /* Passed-in name is the full name */
        RtlCopyUnicodeString(&FileNameU, pFileNameU);

        //  Trivial case, open of the root directory on volume
        if (RtlEqualUnicodeString(&FileNameU, &RootNameU, FALSE))
        {
            DPRINT("returning root FCB\n");

            FCB = vfatOpenRootFCB(pVCB);
            *pFCB = FCB;
            *pParentFCB = NULL;

            return (FCB != NULL) ? STATUS_SUCCESS : STATUS_OBJECT_PATH_NOT_FOUND;
        }

        /* Check for an existing FCB */
        FCB = vfatGrabFCBFromTable(pVCB, &FileNameU);
        if (FCB)
        {
            *pFCB = FCB;
            *pParentFCB = FCB->parentFcb;
            vfatGrabFCB(pVCB, *pParentFCB);
            return STATUS_SUCCESS;
        }

        last = curr = FileNameU.Buffer + FileNameU.Length / sizeof(WCHAR) - 1;
        while (*curr != L'\\' && curr > FileNameU.Buffer)
        {
            curr--;
        }

        if (curr > FileNameU.Buffer)
        {
            NameU.Buffer = FileNameU.Buffer;
            NameU.MaximumLength = NameU.Length = (curr - FileNameU.Buffer) * sizeof(WCHAR);
            FCB = vfatGrabFCBFromTable(pVCB, &NameU);
            if (FCB)
            {
                Length = (curr - FileNameU.Buffer) * sizeof(WCHAR);
                if (Length != FCB->PathNameU.Length)
                {
                    if (FileNameU.Length + FCB->PathNameU.Length - Length > FileNameU.MaximumLength)
                    {
                        vfatReleaseFCB(pVCB, FCB);
                        return STATUS_OBJECT_NAME_INVALID;
                    }
                    RtlMoveMemory(FileNameU.Buffer + FCB->PathNameU.Length / sizeof(WCHAR),
                        curr, FileNameU.Length - Length);
                    FileNameU.Length += (USHORT)(FCB->PathNameU.Length - Length);
                    curr = FileNameU.Buffer + FCB->PathNameU.Length / sizeof(WCHAR);
                    last = FileNameU.Buffer + FileNameU.Length / sizeof(WCHAR) - 1;
                }
                RtlCopyMemory(FileNameU.Buffer, FCB->PathNameU.Buffer, FCB->PathNameU.Length);
            }
        }
        else
        {
            FCB = NULL;
        }

        if (FCB == NULL)
        {
            FCB = vfatOpenRootFCB(pVCB);
            curr = FileNameU.Buffer;
        }

        parentFCB = NULL;
        prev = curr;
    }
    else
    {
        /* Make absolute path */
        RtlCopyUnicodeString(&FileNameU, &parentFCB->PathNameU);
        curr = FileNameU.Buffer + FileNameU.Length / sizeof(WCHAR) - 1;
        if (*curr != L'\\')
        {
            RtlAppendUnicodeToString(&FileNameU, L"\\");
            curr++;
        }
        ASSERT(*curr == L'\\');
        RtlAppendUnicodeStringToString(&FileNameU, pFileNameU);

        FCB = parentFCB;
        parentFCB = NULL;
        prev = curr;
        last = FileNameU.Buffer + FileNameU.Length / sizeof(WCHAR) - 1;
    }

    while (curr <= last)
    {
        if (parentFCB)
        {
            vfatReleaseFCB(pVCB, parentFCB);
            parentFCB = NULL;
        }
        //  fail if element in FCB is not a directory
        if (!vfatFCBIsDirectory(FCB))
        {
            DPRINT ("Element in requested path is not a directory\n");

            vfatReleaseFCB(pVCB, FCB);
            FCB = NULL;
            *pParentFCB = NULL;
            *pFCB = NULL;

            return  STATUS_OBJECT_PATH_NOT_FOUND;
        }
        parentFCB = FCB;
        if (prev < curr)
        {
            Length = (curr - prev) * sizeof(WCHAR);
            if (Length != parentFCB->LongNameU.Length)
            {
                if (FileNameU.Length + parentFCB->LongNameU.Length - Length > FileNameU.MaximumLength)
                {
                    vfatReleaseFCB(pVCB, parentFCB);
                    *pParentFCB = NULL;
                    *pFCB = NULL;
                    return STATUS_OBJECT_NAME_INVALID;
                }
                RtlMoveMemory(prev + parentFCB->LongNameU.Length / sizeof(WCHAR), curr,
                    FileNameU.Length - (curr - FileNameU.Buffer) * sizeof(WCHAR));
                FileNameU.Length += (USHORT)(parentFCB->LongNameU.Length - Length);
                curr = prev + parentFCB->LongNameU.Length / sizeof(WCHAR);
                last = FileNameU.Buffer + FileNameU.Length / sizeof(WCHAR) - 1;
            }
            RtlCopyMemory(prev, parentFCB->LongNameU.Buffer, parentFCB->LongNameU.Length);
        }
        curr++;
        prev = curr;
        while (*curr != L'\\' && curr <= last)
        {
            curr++;
        }
        NameU.Buffer = FileNameU.Buffer;
        NameU.Length = (curr - NameU.Buffer) * sizeof(WCHAR);
        NameU.MaximumLength = FileNameU.MaximumLength;
        DPRINT("%wZ\n", &NameU);
        FCB = vfatGrabFCBFromTable(pVCB, &NameU);
        if (FCB == NULL)
        {
            NameU.Buffer = prev;
            NameU.MaximumLength = NameU.Length = (curr - prev) * sizeof(WCHAR);
            status = vfatDirFindFile(pVCB, parentFCB, &NameU, &FCB);
            if (status == STATUS_OBJECT_NAME_NOT_FOUND)
            {
                *pFCB = NULL;
                if (curr > last)
                {
                    *pParentFCB = parentFCB;
                    return STATUS_OBJECT_NAME_NOT_FOUND;
                }
                else
                {
                    vfatReleaseFCB(pVCB, parentFCB);
                    *pParentFCB = NULL;
                    return STATUS_OBJECT_PATH_NOT_FOUND;
                }
            }
            else if (!NT_SUCCESS(status))
            {
                vfatReleaseFCB(pVCB, parentFCB);
                *pParentFCB = NULL;
                *pFCB = NULL;

                return status;
            }
        }
    }

    *pParentFCB = parentFCB;
    *pFCB = FCB;

    return STATUS_SUCCESS;
}