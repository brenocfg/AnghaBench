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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  i64 ;
typedef  int /*<<< orphan*/  FSE_dtable ;

/* Variables and functions */
 int /*<<< orphan*/  const FSE_peek_symbol (int /*<<< orphan*/  const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSE_update_state (int /*<<< orphan*/  const* const,int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static inline u8 FSE_decode_symbol(const FSE_dtable *const dtable,
                                   u16 *const state, const u8 *const src,
                                   i64 *const offset) {
    const u8 symb = FSE_peek_symbol(dtable, *state);
    FSE_update_state(dtable, state, src, offset);
    return symb;
}