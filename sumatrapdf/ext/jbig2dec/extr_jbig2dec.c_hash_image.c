#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hash_ctx; } ;
typedef  TYPE_1__ jbig2dec_params_t ;
struct TYPE_6__ {unsigned int stride; unsigned int height; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ Jbig2Image ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1_Update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
hash_image(jbig2dec_params_t *params, Jbig2Image *image)
{
    unsigned int N = image->stride * image->height;

    SHA1_Update(params->hash_ctx, image->data, N);
}