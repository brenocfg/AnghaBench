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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_descriptors; int /*<<< orphan*/  p_descriptors; } ;
typedef  TYPE_1__ en50221_capmt_es_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  en50221_capmt_CADescriptorAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void en50221_capmt_AddESCADescriptor( en50221_capmt_es_info_t *p_es,
                                                    const uint8_t *p_data, uint8_t i_data )
{
    en50221_capmt_CADescriptorAppend( &p_es->p_descriptors, &p_es->i_descriptors,
                                       p_data, i_data );
}