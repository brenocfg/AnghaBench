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
struct StringHashTable {unsigned int TableSize; struct StringEntry** Table; } ;
struct StringEntry {int Offset; struct StringEntry* Next; int /*<<< orphan*/  String; } ;
typedef  int ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  AddStringToHash (struct StringHashTable*,unsigned int,int,char*) ; 
 unsigned int ComputeDJBHash (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static ULONG
FindOrAddString(struct StringHashTable *StringTable,
                char *StringToFind,
                ULONG *StringsLength,
                void *StringsBase)
{
    unsigned int hash = ComputeDJBHash(StringToFind) % StringTable->TableSize;
    struct StringEntry *entry = StringTable->Table[hash];

    while (entry && strcmp(entry->String, StringToFind))
        entry = entry->Next;

    if (entry)
    {
        return entry->Offset;
    }
    else
    {
        char *End = (char *)StringsBase + *StringsLength;

        strcpy(End, StringToFind);
        *StringsLength += strlen(StringToFind) + 1;

        AddStringToHash(StringTable, hash, End - (char *)StringsBase, End);

        return End - (char *)StringsBase;
    }
}