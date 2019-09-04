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
struct TYPE_5__ {char const* ptr; int len; } ;
typedef  TYPE_1__ xmlstr_t ;
struct TYPE_6__ {char const* ptr; char const* end; } ;
typedef  TYPE_2__ xmlbuf_t ;
typedef  char WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  isxmlspace (char const) ; 
 char* memchrW (char const*,char,int) ; 

__attribute__((used)) static BOOL next_xml_elem(xmlbuf_t* xmlbuf, xmlstr_t* elem)
{
    const WCHAR* ptr;

    for (;;)
    {
        ptr = memchrW(xmlbuf->ptr, '<', xmlbuf->end - xmlbuf->ptr);
        if (!ptr)
        {
            xmlbuf->ptr = xmlbuf->end;
            return FALSE;
        }
        ptr++;
        if (ptr + 3 < xmlbuf->end && ptr[0] == '!' && ptr[1] == '-' && ptr[2] == '-') /* skip comment */
        {
            for (ptr += 3; ptr + 3 <= xmlbuf->end; ptr++)
                if (ptr[0] == '-' && ptr[1] == '-' && ptr[2] == '>') break;

            if (ptr + 3 > xmlbuf->end)
            {
                xmlbuf->ptr = xmlbuf->end;
                return FALSE;
            }
            xmlbuf->ptr = ptr + 3;
        }
        else break;
    }

    xmlbuf->ptr = ptr;
    while (ptr < xmlbuf->end && !isxmlspace(*ptr) && *ptr != '>' && (*ptr != '/' || ptr == xmlbuf->ptr))
        ptr++;

    elem->ptr = xmlbuf->ptr;
    elem->len = ptr - xmlbuf->ptr;
    xmlbuf->ptr = ptr;
    return xmlbuf->ptr != xmlbuf->end;
}