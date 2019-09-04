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
typedef  int /*<<< orphan*/  type_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  TDT_ALL_TYPES ; 
#define  TGT_ARRAY 132 
#define  TGT_IFACE_POINTER 131 
#define  TGT_STRUCT 130 
#define  TGT_UNION 129 
#define  TGT_USER_TYPE 128 
 int TRUE ; 
 int typegen_detect_type (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_embedded_complex(const type_t *type)
{
    switch (typegen_detect_type(type, NULL, TDT_ALL_TYPES))
    {
    case TGT_USER_TYPE:
    case TGT_STRUCT:
    case TGT_UNION:
    case TGT_ARRAY:
    case TGT_IFACE_POINTER:
        return TRUE;
    default:
        return FALSE;
    }
}