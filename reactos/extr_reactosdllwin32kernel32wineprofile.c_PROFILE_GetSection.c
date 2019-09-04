#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_5__ {int /*<<< orphan*/ * value; int /*<<< orphan*/ * name; struct TYPE_5__* next; } ;
struct TYPE_4__ {struct TYPE_4__* next; TYPE_2__* key; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ PROFILESECTION ;
typedef  TYPE_2__ PROFILEKEY ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ IS_ENTRY_COMMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROFILE_CopyEntry (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlenW (char*) ; 

__attribute__((used)) static INT PROFILE_GetSection( PROFILESECTION *section, LPCWSTR section_name,
#ifdef __REACTOS__
			       LPWSTR buffer, DWORD len, BOOL return_values )
#else
			       LPWSTR buffer, UINT len, BOOL return_values )
#endif
{
    PROFILEKEY *key;

    if(!buffer) return 0;

    TRACE("%s,%p,%u\n", debugstr_w(section_name), buffer, len);

    while (section)
    {
        if (!strcmpiW( section->name, section_name ))
        {
            UINT oldlen = len;
            for (key = section->key; key; key = key->next)
            {
                if (len <= 2) break;
                if (!*key->name) continue;  /* Skip empty lines */
                if (IS_ENTRY_COMMENT(key->name)) continue;  /* Skip comments */
                if (!return_values && !key->value) continue;  /* Skip lines w.o. '=' */
                PROFILE_CopyEntry( buffer, key->name, len - 1, 0 );
                len -= strlenW(buffer) + 1;
                buffer += strlenW(buffer) + 1;
		if (len < 2)
		    break;
		if (return_values && key->value) {
			buffer[-1] = '=';
			PROFILE_CopyEntry ( buffer, key->value, len - 1, 0 );
			len -= strlenW(buffer) + 1;
			buffer += strlenW(buffer) + 1;
                }
            }
            *buffer = '\0';
            if (len <= 1)
                /*If either lpszSection or lpszKey is NULL and the supplied
                  destination buffer is too small to hold all the strings,
                  the last string is truncated and followed by two null characters.
                  In this case, the return value is equal to cchReturnBuffer
                  minus two. */
            {
		buffer[-1] = '\0';
                return oldlen - 2;
            }
            return oldlen - len;
        }
        section = section->next;
    }
    buffer[0] = buffer[1] = '\0';
    return 0;
}