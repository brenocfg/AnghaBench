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
 int /*<<< orphan*/  DC4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  HD4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  HE4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  HU4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int I4DC4 ; 
 int I4HD4 ; 
 int I4HE4 ; 
 int I4HU4 ; 
 int I4LD4 ; 
 int I4RD4 ; 
 int I4TM4 ; 
 int I4VE4 ; 
 int I4VL4 ; 
 int I4VR4 ; 
 int /*<<< orphan*/  LD4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RD4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TM4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VE4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VL4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  VR4 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void Intra4Preds_C(uint8_t* dst, const uint8_t* top) {
  DC4(I4DC4 + dst, top);
  TM4(I4TM4 + dst, top);
  VE4(I4VE4 + dst, top);
  HE4(I4HE4 + dst, top);
  RD4(I4RD4 + dst, top);
  VR4(I4VR4 + dst, top);
  LD4(I4LD4 + dst, top);
  VL4(I4VL4 + dst, top);
  HD4(I4HD4 + dst, top);
  HU4(I4HU4 + dst, top);
}