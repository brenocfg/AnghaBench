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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  guint32 ;

/* Variables and functions */
 int SEAF_METADATA_TYPE_INVALID ; 
 scalar_t__ get32bit (int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int
parse_metadata_type_v0 (const uint8_t *data, int len)
{
    const uint8_t *ptr = data;

    if (len < sizeof(guint32))
        return SEAF_METADATA_TYPE_INVALID;

    return (int)(get32bit(&ptr));
}