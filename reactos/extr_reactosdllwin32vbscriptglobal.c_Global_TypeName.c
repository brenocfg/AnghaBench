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
typedef  int /*<<< orphan*/  vbdisp_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
#define  VT_BOOL 139 
#define  VT_BSTR 138 
#define  VT_CY 137 
#define  VT_DATE 136 
#define  VT_DECIMAL 135 
#define  VT_EMPTY 134 
#define  VT_I2 133 
#define  VT_I4 132 
#define  VT_NULL 131 
#define  VT_R4 130 
#define  VT_R8 129 
#define  VT_UI1 128 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_string (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static HRESULT Global_TypeName(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    static const WCHAR ByteW[]     = {'B', 'y', 't', 'e', 0};
    static const WCHAR IntegerW[]  = {'I', 'n', 't', 'e', 'g', 'e', 'r', 0};
    static const WCHAR LongW[]     = {'L', 'o', 'n', 'g', 0};
    static const WCHAR SingleW[]   = {'S', 'i', 'n', 'g', 'l', 'e', 0};
    static const WCHAR DoubleW[]   = {'D', 'o', 'u', 'b', 'l', 'e', 0};
    static const WCHAR CurrencyW[] = {'C', 'u', 'r', 'r', 'e', 'n', 'c', 'y', 0};
    static const WCHAR DecimalW[]  = {'D', 'e', 'c', 'i', 'm', 'a', 'l', 0};
    static const WCHAR DateW[]     = {'D', 'a', 't', 'e', 0};
    static const WCHAR StringW[]   = {'S', 't', 'r', 'i', 'n', 'g', 0};
    static const WCHAR BooleanW[]  = {'B', 'o', 'o', 'l', 'e', 'a', 'n', 0};
    static const WCHAR EmptyW[]    = {'E', 'm', 'p', 't', 'y', 0};
    static const WCHAR NullW[]     = {'N', 'u', 'l', 'l', 0};

    TRACE("(%s)\n", debugstr_variant(arg));

    assert(args_cnt == 1);

    switch(V_VT(arg)) {
        case VT_UI1:
            return return_string(res, ByteW);
        case VT_I2:
            return return_string(res, IntegerW);
        case VT_I4:
            return return_string(res, LongW);
        case VT_R4:
            return return_string(res, SingleW);
        case VT_R8:
            return return_string(res, DoubleW);
        case VT_CY:
            return return_string(res, CurrencyW);
        case VT_DECIMAL:
            return return_string(res, DecimalW);
        case VT_DATE:
            return return_string(res, DateW);
        case VT_BSTR:
            return return_string(res, StringW);
        case VT_BOOL:
            return return_string(res, BooleanW);
        case VT_EMPTY:
            return return_string(res, EmptyW);
        case VT_NULL:
            return return_string(res, NullW);
        default:
            FIXME("arg %s not supported\n", debugstr_variant(arg));
            return E_NOTIMPL;
        }
}