#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  parser_ctx_t ;
struct TYPE_3__ {int token; int /*<<< orphan*/  word; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int check_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* keywords ; 

__attribute__((used)) static int check_keywords(parser_ctx_t *ctx)
{
    int min = 0, max = ARRAY_SIZE(keywords)-1, r, i;

    while(min <= max) {
        i = (min+max)/2;

        r = check_keyword(ctx, keywords[i].word);
        if(!r)
            return keywords[i].token;

        if(r > 0)
            min = i+1;
        else
            max = i-1;
    }

    return 0;
}