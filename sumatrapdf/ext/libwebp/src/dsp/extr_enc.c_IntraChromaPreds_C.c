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
 int C8DC8 ; 
 int C8HE8 ; 
 int C8TM8 ; 
 int C8VE8 ; 
 int /*<<< orphan*/  DCMode (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  HorizontalPred (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  TrueMotion (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  VerticalPred (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void IntraChromaPreds_C(uint8_t* dst, const uint8_t* left,
                               const uint8_t* top) {
  // U block
  DCMode(C8DC8 + dst, left, top, 8, 8, 4);
  VerticalPred(C8VE8 + dst, top, 8);
  HorizontalPred(C8HE8 + dst, left, 8);
  TrueMotion(C8TM8 + dst, left, top, 8);
  // V block
  dst += 8;
  if (top != NULL) top += 8;
  if (left != NULL) left += 16;
  DCMode(C8DC8 + dst, left, top, 8, 8, 4);
  VerticalPred(C8VE8 + dst, top, 8);
  HorizontalPred(C8HE8 + dst, left, 8);
  TrueMotion(C8TM8 + dst, left, top, 8);
}