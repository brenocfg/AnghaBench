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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  dictionary_t ;

/* Variables and functions */
 size_t const MAX_COMPRESSION_RATIO ; 
 size_t MAX_OUTPUT_SIZE ; 
 size_t ZSTD_decompress_with_dict (int /*<<< orphan*/ * const,size_t,int /*<<< orphan*/ *,size_t const,int /*<<< orphan*/ * const) ; 
 size_t ZSTD_get_decompressed_size (int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/ * create_dictionary () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_dictionary (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  parse_dictionary (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,size_t) ; 
 void* read_file (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  write_file (char*,int /*<<< orphan*/ * const,size_t const) ; 

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s <file.zst> <out_path> [dictionary] \n",
                argv[0]);

        return 1;
    }

    u8* input;
    size_t const input_size = read_file(argv[1], &input);

    u8* dict = NULL;
    size_t dict_size = 0;
    if (argc >= 4) {
        dict_size = read_file(argv[3], &dict);
    }

    size_t out_capacity = ZSTD_get_decompressed_size(input, input_size);
    if (out_capacity == (size_t)-1) {
        out_capacity = MAX_COMPRESSION_RATIO * input_size;
        fprintf(stderr, "WARNING: Compressed data does not contain "
                        "decompressed size, going to assume the compression "
                        "ratio is at most %d (decompressed size of at most "
                        "%u) \n",
                MAX_COMPRESSION_RATIO, (unsigned)out_capacity);
    }
    if (out_capacity > MAX_OUTPUT_SIZE) {
        fprintf(stderr,
                "Required output size too large for this implementation \n");
        return 1;
    }

    u8* const output = malloc(out_capacity);
    if (!output) {
        fprintf(stderr, "failed to allocate memory \n");
        return 1;
    }

    dictionary_t* const parsed_dict = create_dictionary();
    if (dict) {
        parse_dictionary(parsed_dict, dict, dict_size);
    }
    size_t const decompressed_size =
        ZSTD_decompress_with_dict(output, out_capacity,
                                  input, input_size,
                                  parsed_dict);

    free_dictionary(parsed_dict);

    write_file(argv[2], output, decompressed_size);

    free(input);
    free(output);
    free(dict);
    return 0;
}