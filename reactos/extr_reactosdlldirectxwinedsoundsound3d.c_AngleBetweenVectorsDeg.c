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
typedef  int /*<<< orphan*/  D3DVECTOR ;
typedef  int /*<<< orphan*/  D3DVALUE ;

/* Variables and functions */
 int /*<<< orphan*/  AngleBetweenVectorsRad (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RadToDeg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline D3DVALUE AngleBetweenVectorsDeg (const D3DVECTOR *a, const D3DVECTOR *b)
{
	return RadToDeg(AngleBetweenVectorsRad(a, b));
}