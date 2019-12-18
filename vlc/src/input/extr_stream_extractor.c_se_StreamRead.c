#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* pf_read ) (TYPE_2__*,void*,size_t) ;} ;
struct stream_extractor_private {TYPE_2__ extractor; } ;
struct TYPE_4__ {struct stream_extractor_private* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,void*,size_t) ; 

__attribute__((used)) static ssize_t
se_StreamRead( stream_t* stream, void* buf, size_t len )
{
    struct stream_extractor_private* priv = stream->p_sys;
    return priv->extractor.pf_read( &priv->extractor, buf, len );
}