#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t _allocedCount; int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__* MMPointArrayRef ;
typedef  int /*<<< orphan*/  MMPointArray ;
typedef  int /*<<< orphan*/  MMPoint ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 

MMPointArrayRef createMMPointArray(size_t initialCount)
{
	MMPointArrayRef pointArray = calloc(1, sizeof(MMPointArray));

	if (initialCount == 0) initialCount = 1;

	pointArray->_allocedCount = initialCount;
	pointArray->array = malloc(pointArray->_allocedCount * sizeof(MMPoint));
	if (pointArray->array == NULL) return NULL;

	return pointArray;
}