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
struct TYPE_5__ {int* typelib_guidhash_segment; int /*<<< orphan*/ ** typelib_segment_data; } ;
typedef  TYPE_1__ msft_typelib_t ;
struct TYPE_6__ {int next_hash; } ;
typedef  int /*<<< orphan*/  REFGUID ;
typedef  TYPE_2__ MSFT_GuidEntry ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 size_t MSFT_SEG_GUID ; 
 int /*<<< orphan*/  memcmp (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ctl2_find_guid(
	msft_typelib_t *typelib,   /* [I] The typelib to operate against. */
	int hash_key,              /* [I] The hash key for the guid. */
	REFGUID guid)              /* [I] The guid to find. */
{
    int offset;
    MSFT_GuidEntry *guidentry;

    offset = typelib->typelib_guidhash_segment[hash_key];
    while (offset != -1) {
	guidentry = (MSFT_GuidEntry *)&typelib->typelib_segment_data[MSFT_SEG_GUID][offset];

	if (!memcmp(guidentry, guid, sizeof(GUID))) return offset;

	offset = guidentry->next_hash;
    }

    return offset;
}