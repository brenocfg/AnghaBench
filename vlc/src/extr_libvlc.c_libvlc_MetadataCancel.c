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
struct TYPE_3__ {int /*<<< orphan*/ * parser; } ;
typedef  TYPE_1__ libvlc_priv_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_preparser_Cancel (int /*<<< orphan*/ *,void*) ; 
 TYPE_1__* libvlc_priv (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void libvlc_MetadataCancel(libvlc_int_t *libvlc, void *id)
{
    libvlc_priv_t *priv = libvlc_priv(libvlc);

    if (unlikely(priv->parser == NULL))
        return;

    input_preparser_Cancel(priv->parser, id);
}