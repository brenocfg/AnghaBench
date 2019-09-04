#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* resume; } ;
typedef  TYPE_1__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_PENDING ; 
 int /*<<< orphan*/  NC_E_QNAMECOLON ; 
 int /*<<< orphan*/  S_OK ; 
 size_t XmlReadResume_Local ; 
 scalar_t__ is_ncnamechar (char) ; 
 scalar_t__ is_reader_pending (TYPE_1__*) ; 
 scalar_t__ reader_get_cur (TYPE_1__*) ; 
 char* reader_get_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  reader_init_strvalue (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_1__*,int) ; 

__attribute__((used)) static HRESULT reader_parse_local(xmlreader *reader, strval *local, BOOL check_for_separator)
{
    WCHAR *ptr;
    UINT start;

    if (reader->resume[XmlReadResume_Local])
    {
        start = reader->resume[XmlReadResume_Local];
        ptr = reader_get_ptr(reader);
    }
    else
    {
        ptr = reader_get_ptr(reader);
        start = reader_get_cur(reader);
    }

    while (is_ncnamechar(*ptr))
    {
        reader_skipn(reader, 1);
        ptr = reader_get_ptr(reader);
    }

    if (check_for_separator && *ptr == ':')
        return NC_E_QNAMECOLON;

    if (is_reader_pending(reader))
    {
         reader->resume[XmlReadResume_Local] = start;
         return E_PENDING;
    }
    else
         reader->resume[XmlReadResume_Local] = 0;

    reader_init_strvalue(start, reader_get_cur(reader)-start, local);

    return S_OK;
}