#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t nbDDict; int /*<<< orphan*/ ** ddicts; } ;
typedef  TYPE_1__ ddict_collection_t ;
typedef  int /*<<< orphan*/  ZSTD_DDict ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTD_createDDict (void const*,size_t) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__ kNullDDictCollection ; 
 int /*<<< orphan*/ ** malloc (size_t) ; 

__attribute__((used)) static ddict_collection_t createDDictCollection(const void* dictBuffer, size_t dictSize, size_t nbDDict)
{
    ZSTD_DDict** const ddicts = malloc(nbDDict * sizeof(ZSTD_DDict*));
    assert(ddicts != NULL);
    if (ddicts==NULL) return kNullDDictCollection;
    for (size_t dictNb=0; dictNb < nbDDict; dictNb++) {
        ddicts[dictNb] = ZSTD_createDDict(dictBuffer, dictSize);
        assert(ddicts[dictNb] != NULL);
    }
    ddict_collection_t ddictc;
    ddictc.ddicts = ddicts;
    ddictc.nbDDict = nbDDict;
    return ddictc;
}