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
typedef  scalar_t__ LPCWSTR ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
#define  COND_EQ 139 
#define  COND_GE 138 
#define  COND_GT 137 
#define  COND_IEQ 136 
#define  COND_IGE 135 
#define  COND_IGT 134 
#define  COND_ILE 133 
#define  COND_ILT 132 
#define  COND_INE 131 
#define  COND_LE 130 
#define  COND_LT 129 
#define  COND_NE 128 
 int COND_RHS ; 
 int COND_SS ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  atoiW (scalar_t__) ; 
 int compare_int (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int compare_substring (scalar_t__,int,scalar_t__) ; 
 scalar_t__ str_is_number (scalar_t__) ; 
 int /*<<< orphan*/  strcmpW (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strcmpiW (scalar_t__,scalar_t__) ; 
 scalar_t__ szEmpty ; 

__attribute__((used)) static INT compare_string( LPCWSTR a, INT operator, LPCWSTR b, BOOL convert )
{
    if (operator >= COND_SS && operator <= COND_RHS)
        return compare_substring( a, operator, b );

    /* null and empty string are equivalent */
    if (!a) a = szEmpty;
    if (!b) b = szEmpty;

    if (convert && str_is_number(a) && str_is_number(b))
        return compare_int( atoiW(a), operator, atoiW(b) );

    /* a or b may be NULL */
    switch (operator)
    {
    case COND_LT:
        return strcmpW( a, b ) < 0;
    case COND_GT:
        return strcmpW( a, b ) > 0;
    case COND_EQ:
        return strcmpW( a, b ) == 0;
    case COND_NE:
        return strcmpW( a, b ) != 0;
    case COND_GE:
        return strcmpW( a, b ) >= 0;
    case COND_LE:
        return strcmpW( a, b ) <= 0;
    case COND_ILT:
        return strcmpiW( a, b ) < 0;
    case COND_IGT:
        return strcmpiW( a, b ) > 0;
    case COND_IEQ:
        return strcmpiW( a, b ) == 0;
    case COND_INE:
        return strcmpiW( a, b ) != 0;
    case COND_IGE:
        return strcmpiW( a, b ) >= 0;
    case COND_ILE:
        return strcmpiW( a, b ) <= 0;
    default:
        ERR("invalid string operator\n");
        return 0;
    }
    return 0;
}