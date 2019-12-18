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
struct huffman_code {int /*<<< orphan*/  table; int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct huffman_code*,int /*<<< orphan*/ ,int) ; 

void rar_free_code(struct huffman_code *code)
{
    free(code->tree);
    free(code->table);
    memset(code, 0, sizeof(*code));
}