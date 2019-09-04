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
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  char* LPWSTR ;
typedef  int* LPDWORD ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int REG_BINARY ; 
 int REG_DWORD ; 
 int REG_EXPAND_SZ ; 
 int REG_MULTI_SZ ; 
 int REG_SZ ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  deformat_string (int /*<<< orphan*/ *,char const*,char**) ; 
 scalar_t__* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 scalar_t__ msi_strdupW (char const*,int) ; 
 int strlenW (char const*) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BYTE *parse_value( MSIPACKAGE *package, const WCHAR *value, DWORD len, DWORD *type, DWORD *size )
{
    BYTE *data;

    if (!value)
    {
        *size = sizeof(WCHAR);
        *type = REG_SZ;
        if ((data = msi_alloc( *size ))) *(WCHAR *)data = 0;
        return data;
    }
    if (value[0]=='#' && value[1]!='#' && value[1]!='%')
    {
        if (value[1]=='x')
        {
            LPWSTR ptr;
            CHAR byte[5];
            LPWSTR deformated = NULL;
            int count;

            deformat_string(package, &value[2], &deformated);

            /* binary value type */
            ptr = deformated;
            *type = REG_BINARY;
            if (strlenW(ptr)%2)
                *size = (strlenW(ptr)/2)+1;
            else
                *size = strlenW(ptr)/2;

            data = msi_alloc(*size);

            byte[0] = '0'; 
            byte[1] = 'x'; 
            byte[4] = 0; 
            count = 0;
            /* if uneven pad with a zero in front */
            if (strlenW(ptr)%2)
            {
                byte[2]= '0';
                byte[3]= *ptr;
                ptr++;
                data[count] = (BYTE)strtol(byte,NULL,0);
                count ++;
                TRACE("Uneven byte count\n");
            }
            while (*ptr)
            {
                byte[2]= *ptr;
                ptr++;
                byte[3]= *ptr;
                ptr++;
                data[count] = (BYTE)strtol(byte,NULL,0);
                count ++;
            }
            msi_free(deformated);

            TRACE("Data %i bytes(%i)\n",*size,count);
        }
        else
        {
            LPWSTR deformated;
            LPWSTR p;
            DWORD d = 0;
            deformat_string(package, &value[1], &deformated);

            *type=REG_DWORD; 
            *size = sizeof(DWORD);
            data = msi_alloc(*size);
            p = deformated;
            if (*p == '-')
                p++;
            while (*p)
            {
                if ( (*p < '0') || (*p > '9') )
                    break;
                d *= 10;
                d += (*p - '0');
                p++;
            }
            if (deformated[0] == '-')
                d = -d;
            *(LPDWORD)data = d;
            TRACE("DWORD %i\n",*(LPDWORD)data);

            msi_free(deformated);
        }
    }
    else
    {
        const WCHAR *ptr = value;

        *type = REG_SZ;
        if (value[0] == '#')
        {
            ptr++; len--;
            if (value[1] == '%')
            {
                ptr++; len--;
                *type = REG_EXPAND_SZ;
            }
        }
        data = (BYTE *)msi_strdupW( ptr, len );
        if (len > strlenW( (const WCHAR *)data )) *type = REG_MULTI_SZ;
        *size = (len + 1) * sizeof(WCHAR);
    }
    return data;
}