#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  dwInFlags; int /*<<< orphan*/  cDig; } ;
typedef  int /*<<< orphan*/  OLECHAR ;
typedef  TYPE_1__ NUMPARSE ;
typedef  int /*<<< orphan*/  LCID ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int FAILDIG ; 
 int /*<<< orphan*/  LOCALE_NOUSEROVERRIDE ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  pVarParseNumFromStr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static HRESULT convert_str( const char *str, INT dig, ULONG flags,
                            NUMPARSE *np, BYTE rgb[128], LCID lcid )
{
    OLECHAR buff[128];
    MultiByteToWideChar( CP_ACP,0, str, -1, buff, ARRAY_SIZE( buff ));
    memset( rgb, FAILDIG, 128 );
    memset( np, 255, sizeof(*np) );
    np->cDig = dig;
    np->dwInFlags = flags;
    return pVarParseNumFromStr( buff, lcid, LOCALE_NOUSEROVERRIDE, np, rgb);
}