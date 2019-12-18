#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Data4; void* Data3; void* Data2; int /*<<< orphan*/  Data1; } ;
typedef  TYPE_1__ vlc_guid_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetDWLE (int /*<<< orphan*/  const*) ; 
 void* GetWLE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static inline void ASF_GetGUID( vlc_guid_t *p_guid, const uint8_t *p_data )
{
    p_guid->Data1 = GetDWLE( p_data );
    p_guid->Data2 = GetWLE( p_data + 4);
    p_guid->Data3 = GetWLE( p_data + 6);
    memcpy( p_guid->Data4, p_data + 8, 8 );
}