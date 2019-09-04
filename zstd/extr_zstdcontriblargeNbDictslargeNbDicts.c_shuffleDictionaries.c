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
struct TYPE_3__ {size_t nbDDict; int /*<<< orphan*/ ** ddicts; } ;
typedef  TYPE_1__ ddict_collection_t ;
typedef  int /*<<< orphan*/  ZSTD_DDict ;

/* Variables and functions */
 size_t const rand () ; 

void shuffleDictionaries(ddict_collection_t dicts)
{
    size_t const nbDicts = dicts.nbDDict;
    for (size_t r=0; r<nbDicts; r++) {
        size_t const d = rand() % nbDicts;
        ZSTD_DDict* tmpd = dicts.ddicts[d];
        dicts.ddicts[d] = dicts.ddicts[r];
        dicts.ddicts[r] = tmpd;
    }
    for (size_t r=0; r<nbDicts; r++) {
        size_t const d1 = rand() % nbDicts;
        size_t const d2 = rand() % nbDicts;
        ZSTD_DDict* tmpd = dicts.ddicts[d1];
        dicts.ddicts[d1] = dicts.ddicts[d2];
        dicts.ddicts[d2] = tmpd;
    }
}