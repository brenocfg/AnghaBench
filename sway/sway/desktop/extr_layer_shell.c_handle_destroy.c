#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct wl_listener {int dummy; } ;
struct sway_output {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  link; } ;
struct TYPE_13__ {int /*<<< orphan*/  link; } ;
struct TYPE_12__ {int /*<<< orphan*/  link; } ;
struct TYPE_11__ {int /*<<< orphan*/  link; } ;
struct TYPE_10__ {int /*<<< orphan*/  link; } ;
struct TYPE_9__ {int /*<<< orphan*/  link; } ;
struct sway_layer_surface {TYPE_8__* layer_surface; TYPE_6__ output_destroy; TYPE_5__ new_popup; TYPE_4__ surface_commit; TYPE_3__ unmap; TYPE_2__ map; TYPE_1__ destroy; int /*<<< orphan*/  link; } ;
struct TYPE_16__ {TYPE_7__* output; scalar_t__ mapped; int /*<<< orphan*/  namespace; } ;
struct TYPE_15__ {struct sway_output* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  arrange_layers (struct sway_output*) ; 
 int /*<<< orphan*/  destroy ; 
 int /*<<< orphan*/  free (struct sway_layer_surface*) ; 
 struct sway_layer_surface* sway_layer ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 int /*<<< orphan*/  unmap (struct sway_layer_surface*) ; 
 struct sway_layer_surface* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_destroy(struct wl_listener *listener, void *data) {
	struct sway_layer_surface *sway_layer =
		wl_container_of(listener, sway_layer, destroy);
	sway_log(SWAY_DEBUG, "Layer surface destroyed (%s)",
		sway_layer->layer_surface->namespace);
	if (sway_layer->layer_surface->mapped) {
		unmap(sway_layer);
	}
	wl_list_remove(&sway_layer->link);
	wl_list_remove(&sway_layer->destroy.link);
	wl_list_remove(&sway_layer->map.link);
	wl_list_remove(&sway_layer->unmap.link);
	wl_list_remove(&sway_layer->surface_commit.link);
	wl_list_remove(&sway_layer->new_popup.link);
	if (sway_layer->layer_surface->output != NULL) {
		struct sway_output *output = sway_layer->layer_surface->output->data;
		if (output != NULL) {
			arrange_layers(output);
			transaction_commit_dirty();
		}
		wl_list_remove(&sway_layer->output_destroy.link);
		sway_layer->layer_surface->output = NULL;
	}
	free(sway_layer);
}