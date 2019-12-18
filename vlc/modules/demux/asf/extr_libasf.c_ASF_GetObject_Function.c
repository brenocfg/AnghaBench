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
typedef  int /*<<< orphan*/  vlc_guid_t ;
struct ASF_Object_Function_entry {int /*<<< orphan*/  p_id; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct ASF_Object_Function_entry const*) ; 
 struct ASF_Object_Function_entry const* ASF_Object_Function ; 
 scalar_t__ guidcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const struct ASF_Object_Function_entry * ASF_GetObject_Function( const vlc_guid_t *id )
{
    for( size_t i = 0; i < ARRAY_SIZE(ASF_Object_Function); i++ )
    {
        if( guidcmp( ASF_Object_Function[i].p_id, id ) )
            return &ASF_Object_Function[i];
    }
    return NULL;
}