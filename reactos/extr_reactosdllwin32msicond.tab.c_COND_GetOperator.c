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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {size_t n; int /*<<< orphan*/ * str; } ;
struct TYPE_4__ {char member_0; char member_1; char member_2; int /*<<< orphan*/  member_3; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  TYPE_2__ COND_input ;

/* Variables and functions */
#define  COND_GE 144 
#define  COND_GT 143 
#define  COND_IEQ 142 
#define  COND_IGE 141 
#define  COND_IGT 140 
#define  COND_ILE 139 
#define  COND_ILHS 138 
#define  COND_ILT 137 
#define  COND_INE 136 
#define  COND_IRHS 135 
#define  COND_ISS 134 
#define  COND_LE 133 
#define  COND_LHS 132 
#define  COND_LT 131 
#define  COND_NE 130 
#define  COND_RHS 129 
#define  COND_SS 128 
 int lstrlenW (int /*<<< orphan*/  const*) ; 
 scalar_t__ strncmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int COND_GetOperator( COND_input *cond )
{
    static const struct {
        const WCHAR str[4];
        int id;
    } table[] = {
        { {'~','<','=',0}, COND_ILE },
        { {'~','>','<',0}, COND_ISS },
        { {'~','>','>',0}, COND_IRHS },
        { {'~','<','>',0}, COND_INE },
        { {'~','>','=',0}, COND_IGE },
        { {'~','<','<',0}, COND_ILHS },
        { {'~','=',0},     COND_IEQ },
        { {'~','<',0},     COND_ILT },
        { {'~','>',0},     COND_IGT },
        { {'>','=',0},     COND_GE  },
        { {'>','<',0},     COND_SS  },
        { {'<','<',0},     COND_LHS },
        { {'<','>',0},     COND_NE  },
        { {'<','=',0},     COND_LE  },
        { {'>','>',0},     COND_RHS },
        { {'>',0},         COND_GT  },
        { {'<',0},         COND_LT  },
        { {0},             0        }
    };
    LPCWSTR p = &cond->str[cond->n];
    int i = 0, len;

    while ( 1 )
    {
        len = lstrlenW( table[i].str );
        if ( !len || 0 == strncmpW( table[i].str, p, len ) )
            break;
        i++;
    }
    cond->n += len;
    return table[i].id;
}