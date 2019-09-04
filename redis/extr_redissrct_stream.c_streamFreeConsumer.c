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
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  pel; } ;
typedef  TYPE_1__ streamConsumer ;

/* Variables and functions */
 int /*<<< orphan*/  raxFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 

void streamFreeConsumer(streamConsumer *sc) {
    raxFree(sc->pel); /* No value free callback: the PEL entries are shared
                         between the consumer and the main stream PEL. */
    sdsfree(sc->name);
    zfree(sc);
}