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
typedef  int /*<<< orphan*/  webvtt_cue_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static webvtt_cue_t * StreamParserGetCueHandler( void *priv )
{
    VLC_UNUSED(priv);
    return malloc( sizeof(webvtt_cue_t) );
}