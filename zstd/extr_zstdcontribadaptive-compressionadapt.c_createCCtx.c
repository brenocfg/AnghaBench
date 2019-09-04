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
typedef  int /*<<< orphan*/  adaptCCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY (char*) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  freeCCtx (int /*<<< orphan*/ * const) ; 
 int initCCtx (int /*<<< orphan*/ * const,unsigned int) ; 

__attribute__((used)) static adaptCCtx* createCCtx(unsigned numJobs)
{

    adaptCCtx* const ctx = calloc(1, sizeof(adaptCCtx));
    if (ctx == NULL) {
        DISPLAY("Error: could not allocate space for context\n");
        return NULL;
    }
    {
        int const error = initCCtx(ctx, numJobs);
        if (error) {
            freeCCtx(ctx);
            return NULL;
        }
        return ctx;
    }
}