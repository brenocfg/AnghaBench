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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  OP_EQ 134 
#define  OP_GE 133 
#define  OP_GT 132 
#define  OP_LE 131 
#define  OP_LIKE 130 
#define  OP_LT 129 
#define  OP_NE 128 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WBEM_E_INVALID_QUERY ; 
 int eval_like (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int strcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static HRESULT eval_strcmp( UINT op, const WCHAR *lstr, const WCHAR *rstr, LONGLONG *val )
{
    if (!lstr || !rstr)
    {
        *val = 0;
        return S_OK;
    }
    switch (op)
    {
    case OP_EQ:
        *val = !strcmpW( lstr, rstr );
        break;
    case OP_GT:
        *val = strcmpW( lstr, rstr ) > 0;
        break;
    case OP_LT:
        *val = strcmpW( lstr, rstr ) < 0;
        break;
    case OP_LE:
        *val = strcmpW( lstr, rstr ) <= 0;
        break;
    case OP_GE:
        *val = strcmpW( lstr, rstr ) >= 0;
        break;
    case OP_NE:
        *val = strcmpW( lstr, rstr );
        break;
    case OP_LIKE:
        *val = eval_like( lstr, rstr );
        break;
    default:
        ERR("unhandled operator %u\n", op);
        return WBEM_E_INVALID_QUERY;
    }
    return S_OK;
}