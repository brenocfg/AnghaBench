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
struct color_fixup_desc {int dummy; } ;
typedef  int /*<<< orphan*/  fixup ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_FIXUP_IDENTITY ; 
 int /*<<< orphan*/  memcmp (struct color_fixup_desc*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline BOOL is_identity_fixup(struct color_fixup_desc fixup)
{
    return !memcmp(&fixup, &COLOR_FIXUP_IDENTITY, sizeof(fixup));
}