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
struct TYPE_3__ {size_t name_id; size_t offset; size_t length; } ;
typedef  TYPE_1__ sfnt_name ;
typedef  scalar_t__ WORD ;
typedef  size_t WCHAR ;
typedef  size_t USHORT ;
typedef  int SIZE_T ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GDI_ERROR ; 
 scalar_t__ GET_BE_WORD (size_t) ; 
 int GetFontData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MS_NAME_TAG ; 
 int /*<<< orphan*/  TRUE ; 
 int match_name_table_language (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,int,...) ; 

__attribute__((used)) static BOOL get_ttf_nametable_entry(HDC hdc, WORD name_id, WCHAR *out_buf, SIZE_T out_size, LCID language_id)
{
    struct sfnt_name_header
    {
        USHORT format;
        USHORT number_of_record;
        USHORT storage_offset;
    } *header;
    sfnt_name *entry;
    BOOL r = FALSE;
    LONG size, offset, length;
    LONG c, ret;
    WCHAR *name;
    BYTE *data;
    USHORT i;
    int res, best_lang = 0, best_index = -1;

    size = GetFontData(hdc, MS_NAME_TAG, 0, NULL, 0);
    ok(size != GDI_ERROR, "no name table found\n");
    if(size == GDI_ERROR) return FALSE;

    data = HeapAlloc(GetProcessHeap(), 0, size);
    ret = GetFontData(hdc, MS_NAME_TAG, 0, data, size);
    ok(ret == size, "GetFontData should return %u not %u\n", size, ret);

    header = (void *)data;
    header->format = GET_BE_WORD(header->format);
    header->number_of_record = GET_BE_WORD(header->number_of_record);
    header->storage_offset = GET_BE_WORD(header->storage_offset);
    if (header->format != 0)
    {
        trace("got format %u\n", header->format);
        goto out;
    }
    if (header->number_of_record == 0 || sizeof(*header) + header->number_of_record * sizeof(*entry) > size)
    {
        trace("number records out of range: %d\n", header->number_of_record);
        goto out;
    }
    if (header->storage_offset >= size)
    {
        trace("storage_offset %u > size %u\n", header->storage_offset, size);
        goto out;
    }

    entry = (void *)&header[1];
    for (i = 0; i < header->number_of_record; i++)
    {
        if (GET_BE_WORD(entry[i].name_id) != name_id) continue;
        res = match_name_table_language( &entry[i], language_id);
        if (res > best_lang)
        {
            best_lang = res;
            best_index = i;
        }
    }

    offset = header->storage_offset + GET_BE_WORD(entry[best_index].offset);
    length = GET_BE_WORD(entry[best_index].length);
    if (offset + length > size)
    {
        trace("entry %d is out of range\n", best_index);
        goto out;
    }
    if (length >= out_size)
    {
        trace("buffer too small for entry %d\n", best_index);
        goto out;
    }

    name = (WCHAR *)(data + offset);
    for (c = 0; c < length / 2; c++)
        out_buf[c] = GET_BE_WORD(name[c]);
    out_buf[c] = 0;

    r = TRUE;

out:
    HeapFree(GetProcessHeap(), 0, data);
    return r;
}