#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* input; } ;
typedef  TYPE_3__ xmlreader ;
typedef  int /*<<< orphan*/  strval ;
struct TYPE_16__ {int written; char* data; int cur; } ;
typedef  TYPE_4__ encoded_buffer ;
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_14__ {TYPE_1__* buffer; } ;
struct TYPE_13__ {TYPE_4__ utf16; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WC_E_DIGIT ; 
 int /*<<< orphan*/  WC_E_HEXDIGIT ; 
 int /*<<< orphan*/  WC_E_SEMICOLON ; 
 int /*<<< orphan*/  WC_E_UNDECLAREDENTITY ; 
 int /*<<< orphan*/  WC_E_XMLCHARACTER ; 
 int /*<<< orphan*/  debug_strval (TYPE_3__*,int /*<<< orphan*/ *) ; 
 char get_predefined_entity (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_char (char) ; 
 scalar_t__ is_wchar_space (char) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int reader_get_cur (TYPE_3__*) ; 
 char* reader_get_ptr (TYPE_3__*) ; 
 char* reader_get_ptr2 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  reader_parse_name (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_3__*,int) ; 

__attribute__((used)) static HRESULT reader_parse_reference(xmlreader *reader)
{
    encoded_buffer *buffer = &reader->input->buffer->utf16;
    WCHAR *start = reader_get_ptr(reader), *ptr;
    UINT cur = reader_get_cur(reader);
    WCHAR ch = 0;
    int len;

    /* skip '&' */
    reader_skipn(reader, 1);
    ptr = reader_get_ptr(reader);

    if (*ptr == '#')
    {
        reader_skipn(reader, 1);
        ptr = reader_get_ptr(reader);

        /* hex char or decimal */
        if (*ptr == 'x')
        {
            reader_skipn(reader, 1);
            ptr = reader_get_ptr(reader);

            while (*ptr != ';')
            {
                if ((*ptr >= '0' && *ptr <= '9'))
                    ch = ch*16 + *ptr - '0';
                else if ((*ptr >= 'a' && *ptr <= 'f'))
                    ch = ch*16 + *ptr - 'a' + 10;
                else if ((*ptr >= 'A' && *ptr <= 'F'))
                    ch = ch*16 + *ptr - 'A' + 10;
                else
                    return ch ? WC_E_SEMICOLON : WC_E_HEXDIGIT;
                reader_skipn(reader, 1);
                ptr = reader_get_ptr(reader);
            }
        }
        else
        {
            while (*ptr != ';')
            {
                if ((*ptr >= '0' && *ptr <= '9'))
                {
                    ch = ch*10 + *ptr - '0';
                    reader_skipn(reader, 1);
                    ptr = reader_get_ptr(reader);
                }
                else
                    return ch ? WC_E_SEMICOLON : WC_E_DIGIT;
            }
        }

        if (!is_char(ch)) return WC_E_XMLCHARACTER;

        /* normalize */
        if (is_wchar_space(ch)) ch = ' ';

        ptr = reader_get_ptr(reader);
        start = reader_get_ptr2(reader, cur);
        len = buffer->written - ((char *)ptr - buffer->data);
        memmove(start + 1, ptr + 1, len);

        buffer->written -= (reader_get_cur(reader) - cur) * sizeof(WCHAR);
        buffer->cur = cur + 1;

        *start = ch;
    }
    else
    {
        strval name;
        HRESULT hr;

        hr = reader_parse_name(reader, &name);
        if (FAILED(hr)) return hr;

        ptr = reader_get_ptr(reader);
        if (*ptr != ';') return WC_E_SEMICOLON;

        /* predefined entities resolve to a single character */
        ch = get_predefined_entity(reader, &name);
        if (ch)
        {
            len = buffer->written - ((char*)ptr - buffer->data) - sizeof(WCHAR);
            memmove(start+1, ptr+1, len);
            buffer->cur = cur + 1;
            buffer->written -= (ptr - start) * sizeof(WCHAR);

            *start = ch;
        }
        else
        {
            FIXME("undeclared entity %s\n", debug_strval(reader, &name));
            return WC_E_UNDECLAREDENTITY;
        }

    }

    return S_OK;
}