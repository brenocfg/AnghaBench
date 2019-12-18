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
typedef  TYPE_1__* synctex_scanner_t ;
typedef  scalar_t__ synctex_node_t ;
struct TYPE_3__ {char* output; char* output_fmt; int version; int pre_unit; int pre_x_offset; int pre_y_offset; int count; double unit; double x_offset; double y_offset; int number_of_lists; scalar_t__* lists_of_friends; int /*<<< orphan*/  sheet; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNCTEX_DISPLAY (int /*<<< orphan*/ ) ; 
 scalar_t__ SYNCTEX_FRIEND (scalar_t__) ; 
 int SYNCTEX_LINE (scalar_t__) ; 
 int SYNCTEX_TAG (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* synctex_node_isa (scalar_t__) ; 

void synctex_scanner_display(synctex_scanner_t scanner) {
	if (NULL == scanner) {
		return;
	}
	printf("The scanner:\noutput:%s\noutput_fmt:%s\nversion:%i\n",scanner->output,scanner->output_fmt,scanner->version);
	printf("pre_unit:%i\nx_offset:%i\ny_offset:%i\n",scanner->pre_unit,scanner->pre_x_offset,scanner->pre_y_offset);
	printf("count:%i\npost_magnification:%f\npost_x_offset:%f\npost_y_offset:%f\n",
		scanner->count,scanner->unit,scanner->x_offset,scanner->y_offset);
	printf("The input:\n");
	SYNCTEX_DISPLAY(scanner->input);
	if (scanner->count<1000) {
		printf("The sheets:\n");
		SYNCTEX_DISPLAY(scanner->sheet);
		printf("The friends:\n");
		if (scanner->lists_of_friends) {
			int i = scanner->number_of_lists;
			synctex_node_t node;
			while(i--) {
				printf("Friend index:%i\n",i);
				node = (scanner->lists_of_friends)[i];
				while(node) {
					printf("%s:%i,%i\n",
						synctex_node_isa(node),
						SYNCTEX_TAG(node),
						SYNCTEX_LINE(node)
					);
					node = SYNCTEX_FRIEND(node);
				}
			}
		}
	} else {
		printf("SyncTeX Warning: Too many objects\n");
	}
}