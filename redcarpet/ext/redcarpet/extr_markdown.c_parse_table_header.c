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
typedef  char uint8_t ;
struct sd_markdown {int dummy; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int MKD_TABLE_ALIGN_L ; 
 int MKD_TABLE_ALIGN_R ; 
 int /*<<< orphan*/  MKD_TABLE_HEADER ; 
 scalar_t__ _isspace (char) ; 
 int* calloc (size_t,int) ; 
 int /*<<< orphan*/  parse_table_row (struct buf*,struct sd_markdown*,char*,size_t,size_t,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
parse_table_header(
	struct buf *ob,
	struct sd_markdown *rndr,
	uint8_t *data,
	size_t size,
	size_t *columns,
	int **column_data)
{
	int pipes;
	size_t i = 0, col, header_end, under_end;

	pipes = 0;
	while (i < size && data[i] != '\n')
		if (data[i++] == '|')
			pipes++;

	if (i == size || pipes == 0)
		return 0;

	header_end = i;

	while (header_end > 0 && _isspace(data[header_end - 1]))
		header_end--;

	if (data[0] == '|')
		pipes--;

	if (header_end && data[header_end - 1] == '|')
		pipes--;

	*columns = pipes + 1;
	*column_data = calloc(*columns, sizeof(int));

	/* Parse the header underline */
	i++;
	if (i < size && data[i] == '|')
		i++;

	under_end = i;
	while (under_end < size && data[under_end] != '\n')
		under_end++;

	for (col = 0; col < *columns && i < under_end; ++col) {
		size_t dashes = 0;

		while (i < under_end && data[i] == ' ')
			i++;

		if (data[i] == ':') {
			i++; (*column_data)[col] |= MKD_TABLE_ALIGN_L;
			dashes++;
		}

		while (i < under_end && data[i] == '-') {
			i++; dashes++;
		}

		if (i < under_end && data[i] == ':') {
			i++; (*column_data)[col] |= MKD_TABLE_ALIGN_R;
			dashes++;
		}

		while (i < under_end && data[i] == ' ')
			i++;

		if (i < under_end && data[i] != '|' && data[i] != '+')
			break;

		if (dashes < 1)
			break;

		i++;
	}

	if (col < *columns)
		return 0;

	parse_table_row(
		ob, rndr, data,
		header_end,
		*columns,
		*column_data,
		MKD_TABLE_HEADER
	);

	return under_end + 1;
}