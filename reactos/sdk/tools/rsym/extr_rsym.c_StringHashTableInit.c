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
struct StringHashTable {int TableSize; int /*<<< orphan*/  Table; } ;
struct StringEntry {int dummy; } ;
typedef  int ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  AddStringToHash (struct StringHashTable*,int,int,char*) ; 
 int ComputeDJBHash (char*) ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
StringHashTableInit(struct StringHashTable *StringTable,
                    ULONG StringsLength,
                    char *StringsBase)
{
    char *Start = StringsBase;
    char *End = StringsBase + StringsLength;
    StringTable->TableSize = 1024;
    StringTable->Table = calloc(1024, sizeof(struct StringEntry *));
    while (Start < End)
    {
        AddStringToHash(StringTable,
                        ComputeDJBHash(Start) % StringTable->TableSize,
                        Start - StringsBase,
                        Start);
        Start += strlen(Start) + 1;
    }
}