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
struct TYPE_5__ {int (* pf_readdir ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct stream_extractor_private {TYPE_2__ directory; } ;
struct TYPE_4__ {struct stream_extractor_private* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
se_ReadDir( stream_t* stream, input_item_node_t* node )
{
    struct stream_extractor_private* priv = stream->p_sys;
    return priv->directory.pf_readdir( &priv->directory, node );
}