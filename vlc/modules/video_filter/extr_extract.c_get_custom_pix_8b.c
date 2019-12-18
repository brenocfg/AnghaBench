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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CUSTOM_PIX () ; 

__attribute__((used)) static inline void
get_custom_pix_8b( uint8_t *y_in[2], uint8_t *y_out[2],
                   uint8_t **u_in, uint8_t **u_out,
                   uint8_t **v_in, uint8_t **v_out,
                   uint16_t const u, uint16_t const v,
                   int const *m, int maxval )
{
    uint8_t val;
    GET_CUSTOM_PIX();
}