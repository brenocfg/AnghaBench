#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ tt_table_directory ;
struct TYPE_8__ {int /*<<< orphan*/  string_offset; int /*<<< orphan*/  count; } ;
typedef  TYPE_2__ tt_name_table ;
struct TYPE_9__ {int /*<<< orphan*/  language_id; int /*<<< orphan*/  platform_id; int /*<<< orphan*/  name_id; int /*<<< orphan*/  offset; int /*<<< orphan*/  length; } ;
typedef  TYPE_3__ tt_name_record ;
struct TYPE_10__ {int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; int /*<<< orphan*/  tables_no; } ;
typedef  TYPE_4__ tt_header ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LANGID ;
typedef  int DWORD_PTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int GET_BE_DWORD (int /*<<< orphan*/ ) ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSystemDefaultLangID () ; 
 int /*<<< orphan*/  TRACE (char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * copy_name_table_string (TYPE_3__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int match_name_table_language (TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static WCHAR *load_ttf_name_id( const BYTE *mem, DWORD_PTR size, DWORD id )
{
    LANGID lang = GetSystemDefaultLangID();
    const tt_header *header;
    const tt_name_table *name_table;
    const tt_name_record *name_record;
    DWORD pos, ofs, count;
    int i, res, best_lang = 0, best_index = -1;

    if (sizeof(tt_header) > size)
        return NULL;
    header = (const tt_header*)mem;
    count = GET_BE_WORD(header->tables_no);

    if (GET_BE_WORD(header->major_version) != 1 || GET_BE_WORD(header->minor_version) != 0)
        return NULL;

    pos = sizeof(*header);
    for (i = 0; i < count; i++)
    {
        const tt_table_directory *table_directory = (const tt_table_directory*)&mem[pos];
        pos += sizeof(*table_directory);
        if (memcmp(table_directory->tag, "name", 4) == 0)
        {
            ofs = GET_BE_DWORD(table_directory->offset);
            break;
        }
    }
    if (i >= count)
        return NULL;

    if (ofs >= size)
        return NULL;
    pos = ofs + sizeof(*name_table);
    if (pos > size)
        return NULL;
    name_table = (const tt_name_table*)&mem[ofs];
    count =  GET_BE_WORD(name_table->count);
    if (GET_BE_WORD(name_table->string_offset) >= size - ofs) return NULL;
    ofs += GET_BE_WORD(name_table->string_offset);
    for (i=0; i<count; i++)
    {
        name_record = (const tt_name_record*)&mem[pos];
        pos += sizeof(*name_record);
        if (pos > size)
            return NULL;

        if (GET_BE_WORD(name_record->name_id) != id) continue;
        if (GET_BE_WORD(name_record->offset) >= size - ofs) return NULL;
        if (GET_BE_WORD(name_record->length) > size - ofs - GET_BE_WORD(name_record->offset)) return NULL;

        res = match_name_table_language( name_record, lang );
        if (res > best_lang)
        {
            best_lang = res;
            best_index = i;
        }
    }

    if (best_lang)
    {
        WCHAR *ret;
        name_record = (const tt_name_record*)(name_table + 1) + best_index;
        ret = copy_name_table_string( name_record, mem+ofs+GET_BE_WORD(name_record->offset) );
        TRACE( "name %u found platform %u lang %04x %s\n", GET_BE_WORD(name_record->name_id),
                GET_BE_WORD(name_record->platform_id), GET_BE_WORD(name_record->language_id), debugstr_w( ret ));
        return ret;
    }
    return NULL;
}