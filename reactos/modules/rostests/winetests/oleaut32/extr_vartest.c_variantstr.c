#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int UINT ;
struct TYPE_2__ {int Hi; int /*<<< orphan*/  Lo; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 TYPE_1__ S (int /*<<< orphan*/ ) ; 
#define  VT_CY 141 
#define  VT_DATE 140 
#define  VT_I1 139 
#define  VT_I2 138 
#define  VT_I4 137 
#define  VT_I8 136 
#define  VT_INT 135 
#define  VT_R4 134 
#define  VT_R8 133 
#define  VT_UI1 132 
#define  VT_UI2 131 
#define  VT_UI4 130 
#define  VT_UI8 129 
#define  VT_UINT 128 
 int /*<<< orphan*/  V_CY (int /*<<< orphan*/  const*) ; 
 double V_DATE (int /*<<< orphan*/  const*) ; 
 int V_I1 (int /*<<< orphan*/  const*) ; 
 int V_I2 (int /*<<< orphan*/  const*) ; 
 int V_I4 (int /*<<< orphan*/  const*) ; 
 int V_I8 (int /*<<< orphan*/  const*) ; 
 int V_INT (int /*<<< orphan*/  const*) ; 
 double V_R4 (int /*<<< orphan*/  const*) ; 
 double V_R8 (int /*<<< orphan*/  const*) ; 
 int V_UI1 (int /*<<< orphan*/  const*) ; 
 int V_UI2 (int /*<<< orphan*/  const*) ; 
 int V_UI4 (int /*<<< orphan*/  const*) ; 
 int V_UI8 (int /*<<< orphan*/  const*) ; 
 int V_UINT (int /*<<< orphan*/  const*) ; 
 int V_VT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sprintf (char const*,char*,double,...) ; 
 char const* vtstr (int) ; 
 char const** vtstr_buffer ; 
 size_t vtstr_current ; 

__attribute__((used)) static const char *variantstr( const VARIANT *var )
{
    vtstr_current %= ARRAY_SIZE(vtstr_buffer);
    switch(V_VT(var))
    {
    case VT_I1:
        sprintf( vtstr_buffer[vtstr_current], "VT_I1(%d)", V_I1(var) ); break;
    case VT_I2:
        sprintf( vtstr_buffer[vtstr_current], "VT_I2(%d)", V_I2(var) ); break;
    case VT_I4:
        sprintf( vtstr_buffer[vtstr_current], "VT_I4(%d)", V_I4(var) ); break;
    case VT_INT:
        sprintf( vtstr_buffer[vtstr_current], "VT_INT(%d)", V_INT(var) ); break;
    case VT_I8:
        sprintf( vtstr_buffer[vtstr_current], "VT_I8(%x%08x)", (UINT)(V_I8(var) >> 32), (UINT)V_I8(var) ); break;
    case VT_UI8:
        sprintf( vtstr_buffer[vtstr_current], "VT_UI8(%x%08x)", (UINT)(V_UI8(var) >> 32), (UINT)V_UI8(var) ); break;
    case VT_R4:
        sprintf( vtstr_buffer[vtstr_current], "VT_R4(%g)", V_R4(var) ); break;
    case VT_R8:
        sprintf( vtstr_buffer[vtstr_current], "VT_R8(%g)", V_R8(var) ); break;
    case VT_UI1:
        sprintf( vtstr_buffer[vtstr_current], "VT_UI1(%u)", V_UI1(var) ); break;
    case VT_UI2:
        sprintf( vtstr_buffer[vtstr_current], "VT_UI2(%u)", V_UI2(var) ); break;
    case VT_UI4:
        sprintf( vtstr_buffer[vtstr_current], "VT_UI4(%u)", V_UI4(var) ); break;
    case VT_UINT:
        sprintf( vtstr_buffer[vtstr_current], "VT_UINT(%d)", V_UINT(var) ); break;
    case VT_CY:
        sprintf( vtstr_buffer[vtstr_current], "VT_CY(%x%08x)", S(V_CY(var)).Hi, S(V_CY(var)).Lo ); break;
    case VT_DATE:
        sprintf( vtstr_buffer[vtstr_current], "VT_DATE(%g)", V_DATE(var) ); break;
    default:
        return vtstr(V_VT(var));
    }
    return vtstr_buffer[vtstr_current++];
}