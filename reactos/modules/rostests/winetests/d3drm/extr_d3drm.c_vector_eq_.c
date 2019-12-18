#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  x; } ;
struct TYPE_5__ {int /*<<< orphan*/  y; } ;
struct TYPE_4__ {int /*<<< orphan*/  z; } ;
typedef  int /*<<< orphan*/  D3DVECTOR ;

/* Variables and functions */
 TYPE_3__ U1 (int /*<<< orphan*/  const) ; 
 TYPE_2__ U2 (int /*<<< orphan*/  const) ; 
 TYPE_1__ U3 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  expect_vector_ (unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vector_eq_(unsigned int line, const D3DVECTOR *left, const D3DVECTOR *right)
{
    expect_vector_(line, left, U1(*right).x, U2(*right).y, U3(*right).z, 0);
}