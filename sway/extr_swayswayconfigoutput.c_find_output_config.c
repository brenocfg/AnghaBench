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
struct sway_output {int dummy; } ;
struct output_config {int dummy; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 struct output_config* get_output_config (char*,struct sway_output*) ; 
 int /*<<< orphan*/  output_get_identifier (char*,int,struct sway_output*) ; 

struct output_config *find_output_config(struct sway_output *output) {
	char id[128];
	output_get_identifier(id, sizeof(id), output);
	return get_output_config(id, output);
}