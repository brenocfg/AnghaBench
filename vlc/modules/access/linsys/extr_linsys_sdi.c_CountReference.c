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

/* Variables and functions */
 int /*<<< orphan*/ * FindReferenceCode (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const uint8_t *CountReference( unsigned int *pi_count, uint8_t i_code,
                                      const uint8_t *p_parser,
                                      const uint8_t *p_end )
{
    const uint8_t *p_tmp = FindReferenceCode( i_code, p_parser, p_end );
    if ( p_tmp == NULL )
    {
        *pi_count += p_end - p_parser;
        return NULL;
    }
    *pi_count += p_tmp - p_parser;
    return p_tmp;
}