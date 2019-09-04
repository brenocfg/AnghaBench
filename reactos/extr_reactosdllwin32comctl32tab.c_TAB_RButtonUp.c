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
typedef  int /*<<< orphan*/  TAB_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  NM_RCLICK ; 
 int /*<<< orphan*/  TAB_SendSimpleNotify (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
TAB_RButtonUp (const TAB_INFO *infoPtr)
{
  TAB_SendSimpleNotify(infoPtr, NM_RCLICK);
}