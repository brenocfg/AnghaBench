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
struct StringHashTable {struct StringEntry** Table; } ;
struct StringEntry {char* String; struct StringEntry* Next; int /*<<< orphan*/  Offset; } ;
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 struct StringEntry* calloc (int,int) ; 

__attribute__((used)) static void
AddStringToHash(struct StringHashTable *StringTable,
                unsigned int hash,
                ULONG Offset,
                char *StringPtr)
{
    struct StringEntry *entry = calloc(1, sizeof(struct StringEntry));
    entry->Offset = Offset;
    entry->String = StringPtr;
    entry->Next = StringTable->Table[hash];
    StringTable->Table[hash] = entry;
}