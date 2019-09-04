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
struct strsection_header {int dummy; } ;
struct string_index {int name_offset; int name_len; int data_offset; int data_len; int rosterindex; int /*<<< orphan*/  hash; } ;
struct progidredirect_data {int size; int clsid_offset; scalar_t__ reserved; } ;
typedef  scalar_t__ WCHAR ;
struct TYPE_4__ {int Length; int /*<<< orphan*/  MaximumLength; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_STRING_ALGORITHM_X65599 ; 
 int /*<<< orphan*/  RtlHashUnicodeString (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,scalar_t__ const*) ; 
 int /*<<< orphan*/  TRUE ; 
 int aligned_string_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 

__attribute__((used)) static void write_progid_record(struct strsection_header *section, const WCHAR *progid, const GUID *alias,
    struct string_index **index, ULONG *data_offset, ULONG *global_offset, ULONG rosterindex)
{
    struct progidredirect_data *data;
    UNICODE_STRING str;
    GUID *guid_ptr;
    WCHAR *ptrW;

    /* setup new index entry */

    /* hash progid name */
    RtlInitUnicodeString(&str, progid);
    RtlHashUnicodeString(&str, TRUE, HASH_STRING_ALGORITHM_X65599, &(*index)->hash);

    (*index)->name_offset = *data_offset;
    (*index)->name_len = str.Length;
    (*index)->data_offset = (*index)->name_offset + aligned_string_len(str.MaximumLength);
    (*index)->data_len = sizeof(*data);
    (*index)->rosterindex = rosterindex;

    *data_offset += aligned_string_len(str.MaximumLength);

    /* setup data structure */
    data = (struct progidredirect_data*)((BYTE*)section + *data_offset);
    data->size = sizeof(*data);
    data->reserved = 0;
    data->clsid_offset = *global_offset;

    /* write progid string */
    ptrW = (WCHAR*)((BYTE*)section + (*index)->name_offset);
    memcpy(ptrW, progid, (*index)->name_len);
    ptrW[(*index)->name_len/sizeof(WCHAR)] = 0;

    /* write guid to global area */
    guid_ptr = (GUID*)((BYTE*)section + data->clsid_offset);
    *guid_ptr = *alias;

    /* to next entry */
    *global_offset += sizeof(GUID);
    *data_offset += data->size;
    (*index) += 1;
}