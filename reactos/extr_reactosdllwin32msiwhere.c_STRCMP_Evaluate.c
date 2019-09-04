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
struct complex_expr {scalar_t__ op; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIWHEREVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int INT ;

/* Variables and functions */
 scalar_t__ ERROR_CONTINUE ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ OP_EQ ; 
 scalar_t__ OP_NE ; 
 scalar_t__ STRING_evaluate (int /*<<< orphan*/ *,scalar_t__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const**) ; 
 int TRUE ; 
 int strcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static UINT STRCMP_Evaluate( MSIWHEREVIEW *wv, const UINT rows[], const struct complex_expr *expr,
                             INT *val, const MSIRECORD *record )
{
    int sr;
    const WCHAR *l_str, *r_str;
    UINT r;

    *val = TRUE;
    r = STRING_evaluate(wv, rows, expr->left, record, &l_str);
    if (r == ERROR_CONTINUE)
        return r;
    r = STRING_evaluate(wv, rows, expr->right, record, &r_str);
    if (r == ERROR_CONTINUE)
        return r;

    if( l_str == r_str ||
        ((!l_str || !*l_str) && (!r_str || !*r_str)) )
        sr = 0;
    else if( l_str && ! r_str )
        sr = 1;
    else if( r_str && ! l_str )
        sr = -1;
    else
        sr = strcmpW( l_str, r_str );

    *val = ( expr->op == OP_EQ && ( sr == 0 ) ) ||
           ( expr->op == OP_NE && ( sr != 0 ) );

    return ERROR_SUCCESS;
}