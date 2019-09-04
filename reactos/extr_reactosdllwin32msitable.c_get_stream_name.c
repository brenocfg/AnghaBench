#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  size_t UINT ;
struct TYPE_8__ {size_t type; } ;
struct TYPE_7__ {int /*<<< orphan*/  strings; } ;
struct TYPE_6__ {char* name; size_t num_cols; TYPE_4__* columns; TYPE_3__* db; } ;
typedef  int /*<<< orphan*/  MSIVIEW ;
typedef  TYPE_1__ MSITABLEVIEW ;
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,size_t) ; 
 size_t ERROR_FUNCTION_FAILED ; 
 size_t ERROR_INVALID_PARAMETER ; 
 size_t ERROR_OUTOFMEMORY ; 
 size_t ERROR_SUCCESS ; 
 int /*<<< orphan*/  LONG_STR_BYTES ; 
 size_t MSITYPE_KEY ; 
 int MSITYPE_STRING ; 
 size_t TABLE_fetch_int (int /*<<< orphan*/ *,size_t,size_t,size_t*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*,size_t) ; 
 size_t bytes_per_column (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcatW (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int lstrlenW (char*) ; 
 char* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_free (char*) ; 
 char* msi_realloc (char*,int) ; 
 char* msi_string_lookup (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,size_t) ; 
 char* szDot ; 

__attribute__((used)) static UINT get_stream_name( const MSITABLEVIEW *tv, UINT row, WCHAR **pstname )
{
    LPWSTR p, stname = NULL;
    UINT i, r, type, ival;
    DWORD len;
    LPCWSTR sval;
    MSIVIEW *view = (MSIVIEW *) tv;

    TRACE("%p %d\n", tv, row);

    len = lstrlenW( tv->name ) + 1;
    stname = msi_alloc( len*sizeof(WCHAR) );
    if ( !stname )
    {
       r = ERROR_OUTOFMEMORY;
       goto err;
    }

    lstrcpyW( stname, tv->name );

    for ( i = 0; i < tv->num_cols; i++ )
    {
        type = tv->columns[i].type;
        if ( type & MSITYPE_KEY )
        {
            WCHAR number[0x20];

            r = TABLE_fetch_int( view, row, i+1, &ival );
            if ( r != ERROR_SUCCESS )
                goto err;

            if ( tv->columns[i].type & MSITYPE_STRING )
            {
                sval = msi_string_lookup( tv->db->strings, ival, NULL );
                if ( !sval )
                {
                    r = ERROR_INVALID_PARAMETER;
                    goto err;
                }
            }
            else
            {
                static const WCHAR fmt[] = { '%','d',0 };
                UINT n = bytes_per_column( tv->db, &tv->columns[i], LONG_STR_BYTES );

                switch( n )
                {
                case 2:
                    sprintfW( number, fmt, ival-0x8000 );
                    break;
                case 4:
                    sprintfW( number, fmt, ival^0x80000000 );
                    break;
                default:
                    ERR( "oops - unknown column width %d\n", n );
                    r = ERROR_FUNCTION_FAILED;
                    goto err;
                }
                sval = number;
            }

            len += lstrlenW( szDot ) + lstrlenW( sval );
            p = msi_realloc ( stname, len*sizeof(WCHAR) );
            if ( !p )
            {
                r = ERROR_OUTOFMEMORY;
                goto err;
            }
            stname = p;

            lstrcatW( stname, szDot );
            lstrcatW( stname, sval );
        }
        else
           continue;
    }

    *pstname = stname;
    return ERROR_SUCCESS;

err:
    msi_free( stname );
    *pstname = NULL;
    return r;
}