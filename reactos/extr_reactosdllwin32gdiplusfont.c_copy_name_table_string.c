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
struct TYPE_4__ {int /*<<< orphan*/  platform_id; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ tt_name_record ;
typedef  int WORD ;
typedef  int WCHAR ;
typedef  int BYTE ;

/* Variables and functions */
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 int MultiByteToWideChar (int,int /*<<< orphan*/ ,char*,int,int*,int) ; 
#define  TT_PLATFORM_APPLE_UNICODE 130 
#define  TT_PLATFORM_MACINTOSH 129 
#define  TT_PLATFORM_MICROSOFT 128 
 int get_mac_code_page (TYPE_1__ const*) ; 
 int* heap_alloc (int) ; 

__attribute__((used)) static WCHAR *copy_name_table_string( const tt_name_record *name, const BYTE *data )
{
    WORD name_len = GET_BE_WORD(name->length);
    WORD codepage;
    WCHAR *ret;
    int len;

    switch (GET_BE_WORD(name->platform_id))
    {
    case TT_PLATFORM_APPLE_UNICODE:
    case TT_PLATFORM_MICROSOFT:
        ret = heap_alloc((name_len / 2 + 1) * sizeof(WCHAR));
        for (len = 0; len < name_len / 2; len++)
            ret[len] = (data[len * 2] << 8) | data[len * 2 + 1];
        ret[len] = 0;
        return ret;
    case TT_PLATFORM_MACINTOSH:
        codepage = get_mac_code_page( name );
        len = MultiByteToWideChar( codepage, 0, (char *)data, name_len, NULL, 0 ) + 1;
        if (!len)
            return NULL;
        ret = heap_alloc(len * sizeof(WCHAR));
        len = MultiByteToWideChar( codepage, 0, (char *)data, name_len, ret, len - 1 );
        ret[len] = 0;
        return ret;
    }
    return NULL;
}