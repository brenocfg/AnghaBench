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
typedef  int /*<<< orphan*/  chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 

__attribute__((used)) static inline chunk_t* chunk_new()
{
    chunk_t* chunk = calloc(1, sizeof(chunk_t));
    return chunk;
}