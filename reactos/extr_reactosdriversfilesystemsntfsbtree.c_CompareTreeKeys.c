#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int Length; int MaximumLength; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_3__ UNICODE_STRING ;
struct TYPE_12__ {TYPE_2__* IndexEntry; int /*<<< orphan*/ * NextKey; } ;
struct TYPE_9__ {int NameLength; int /*<<< orphan*/  Name; } ;
struct TYPE_10__ {int Flags; TYPE_1__ FileName; } ;
typedef  TYPE_4__* PB_TREE_KEY ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int NTFS_INDEX_ENTRY_END ; 
 int RtlCompareUnicodeString (TYPE_3__*,TYPE_3__*,int) ; 

LONG
CompareTreeKeys(PB_TREE_KEY Key1, PB_TREE_KEY Key2, BOOLEAN CaseSensitive)
{
    UNICODE_STRING Key1Name, Key2Name;
    LONG Comparison;

    // Key1 must not be the final key (AKA the dummy key)
    ASSERT(!(Key1->IndexEntry->Flags & NTFS_INDEX_ENTRY_END));

    // If Key2 is the "dummy key", key 1 will always come first
    if (Key2->NextKey == NULL)
        return -1;

    Key1Name.Buffer = Key1->IndexEntry->FileName.Name;
    Key1Name.Length = Key1Name.MaximumLength
        = Key1->IndexEntry->FileName.NameLength * sizeof(WCHAR);

    Key2Name.Buffer = Key2->IndexEntry->FileName.Name;
    Key2Name.Length = Key2Name.MaximumLength
        = Key2->IndexEntry->FileName.NameLength * sizeof(WCHAR);

    // Are the two keys the same length?
    if (Key1Name.Length == Key2Name.Length)
        return RtlCompareUnicodeString(&Key1Name, &Key2Name, !CaseSensitive);

    // Is Key1 shorter?
    if (Key1Name.Length < Key2Name.Length)
    {
        // Truncate KeyName2 to be the same length as KeyName1
        Key2Name.Length = Key1Name.Length;
        
        // Compare the names of the same length
        Comparison = RtlCompareUnicodeString(&Key1Name, &Key2Name, !CaseSensitive);

        // If the truncated names are the same length, the shorter one comes first
        if (Comparison == 0)
            return -1;
    }
    else
    {
        // Key2 is shorter
        // Truncate KeyName1 to be the same length as KeyName2
        Key1Name.Length = Key2Name.Length;

        // Compare the names of the same length
        Comparison = RtlCompareUnicodeString(&Key1Name, &Key2Name, !CaseSensitive);

        // If the truncated names are the same length, the shorter one comes first
        if (Comparison == 0)
            return 1;
    }

    return Comparison;
}