#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char WCHAR ;
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_EncodeBase64 (char const*,int,char*) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static WCHAR *encode_auth_data( const WCHAR *scheme, const char *data, UINT data_len )
{
    WCHAR *ret;
    UINT len, scheme_len = strlenW( scheme );

    /* scheme + space + base64 encoded data (3/2/1 bytes data -> 4 bytes of characters) */
    len = scheme_len + 1 + ((data_len + 2) * 4) / 3;
    if (!(ret = heap_alloc( (len + 1) * sizeof(WCHAR) ))) return NULL;
    memcpy( ret, scheme, scheme_len * sizeof(WCHAR) );
    ret[scheme_len] = ' ';
    HTTP_EncodeBase64( data, data_len, ret + scheme_len + 1 );
    return ret;
}