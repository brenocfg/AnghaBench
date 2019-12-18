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
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_fourcc (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  bo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bo_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 

bo_t *box_new(const char *fcc)
{
    bo_t *box = malloc(sizeof(*box));
    if (!box)
        return NULL;

    if(!bo_init(box, 1024))
    {
        bo_free(box);
        return NULL;
    }

    bo_add_32be  (box, 0);
    bo_add_fourcc(box, fcc);

    return box;
}