#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_fast32_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int i_buffer; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_TYPE_P ; 
 void* CC_PKT_BYTE0 (int /*<<< orphan*/ ) ; 
 int GetDWBE (int /*<<< orphan*/ *) ; 
 int SSIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t * MP4_EIA608_Convert( block_t * p_block )
{
    /* Rebuild codec data from encap */
    block_t *p_newblock = NULL;

    assert(p_block->i_buffer <= SSIZE_MAX);
    /* always need at least 10 bytes (atom size+header+1pair)*/
    if (p_block->i_buffer < 8)
        goto out;

    uint_fast32_t cdat_size = GetDWBE(p_block->p_buffer) - 8;
    if (cdat_size > p_block->i_buffer)
        goto out;

    const uint8_t *cdat = p_block->p_buffer + 8;
    if (memcmp(cdat - 4, "cdat", 4) != 0)
        goto out;

    p_block->p_buffer += cdat_size;
    p_block->i_buffer -= cdat_size;
    cdat_size &= ~1;

    /* cdt2 is optional */
    uint_fast32_t cdt2_size = 0;
    const uint8_t *cdt2;

    if (p_block->i_buffer >= 8) {
        size_t size = GetDWBE(p_block->p_buffer) - 8;

        if (size <= p_block->i_buffer) {
            cdt2 = p_block->p_buffer + 8;

            if (memcmp(cdt2 - 4, "cdt2", 4) == 0)
                cdt2_size = size & ~1;
        }
    }

    p_newblock = block_Alloc((cdat_size + cdt2_size) / 2 * 3);
    if (unlikely(p_newblock == NULL))
        goto out;

    uint8_t *out = p_newblock->p_buffer;

    while (cdat_size > 0) {
         *(out++) = CC_PKT_BYTE0(0); /* cc1 == field 0 */
         *(out++) = *(cdat++);
         *(out++) = *(cdat++);
         cdat_size -= 2;
    }

    while (cdt2_size > 0) {
         *(out++) = CC_PKT_BYTE0(0); /* cc1 == field 0 */
         *(out++) = *(cdt2++);
         *(out++) = *(cdt2++);
         cdt2_size -= 2;
    }

    p_newblock->i_pts = p_block->i_dts;
    p_newblock->i_flags = BLOCK_FLAG_TYPE_P;
out:
    block_Release( p_block );
    return p_newblock;
}