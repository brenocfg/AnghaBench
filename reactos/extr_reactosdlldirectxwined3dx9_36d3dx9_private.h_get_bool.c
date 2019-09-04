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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int D3DXPARAMETER_TYPE ;
typedef  int BOOL ;

/* Variables and functions */
#define  D3DXPT_BOOL 131 
#define  D3DXPT_FLOAT 130 
#define  D3DXPT_INT 129 
#define  D3DXPT_VOID 128 
 int FALSE ; 

__attribute__((used)) static inline BOOL get_bool(D3DXPARAMETER_TYPE type, const void *data)
{
    switch (type)
    {
        case D3DXPT_FLOAT:
        case D3DXPT_INT:
        case D3DXPT_BOOL:
            return !!*(DWORD *)data;

        case D3DXPT_VOID:
            return *(BOOL *)data;

        default:
            return FALSE;
    }
}