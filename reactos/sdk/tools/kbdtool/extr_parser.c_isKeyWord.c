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
typedef  size_t ULONG ;
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
 size_t KEYWORD_COUNT ; 
 int /*<<< orphan*/ * KeyWordList ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ULONG
isKeyWord(PCHAR p)
{
    ULONG i;

    /* Check if we know this keyword */
    for (i = 0; i < KEYWORD_COUNT; i++) if (strcmp(KeyWordList[i], p) == 0) break;

    /* If we didn't find anything, i will be KEYWORD_COUNT, which is invalid */
    return i;
}