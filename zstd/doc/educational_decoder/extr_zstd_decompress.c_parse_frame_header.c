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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  istream_t ;
struct TYPE_3__ {int single_segment_flag; int content_checksum_flag; size_t window_size; int frame_content_size; scalar_t__ dictionary_id; } ;
typedef  TYPE_1__ frame_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORRUPTION () ; 
 int IO_read_bits (int /*<<< orphan*/ * const,int const) ; 

__attribute__((used)) static void parse_frame_header(frame_header_t *const header,
                               istream_t *const in) {
    // "The first header's byte is called the Frame_Header_Descriptor. It tells
    // which other fields are present. Decoding this byte is enough to tell the
    // size of Frame_Header.
    //
    // Bit number   Field name
    // 7-6  Frame_Content_Size_flag
    // 5    Single_Segment_flag
    // 4    Unused_bit
    // 3    Reserved_bit
    // 2    Content_Checksum_flag
    // 1-0  Dictionary_ID_flag"
    const u8 descriptor = (u8)IO_read_bits(in, 8);

    // decode frame header descriptor into flags
    const u8 frame_content_size_flag = descriptor >> 6;
    const u8 single_segment_flag = (descriptor >> 5) & 1;
    const u8 reserved_bit = (descriptor >> 3) & 1;
    const u8 content_checksum_flag = (descriptor >> 2) & 1;
    const u8 dictionary_id_flag = descriptor & 3;

    if (reserved_bit != 0) {
        CORRUPTION();
    }

    header->single_segment_flag = single_segment_flag;
    header->content_checksum_flag = content_checksum_flag;

    // decode window size
    if (!single_segment_flag) {
        // "Provides guarantees on maximum back-reference distance that will be
        // used within compressed data. This information is important for
        // decoders to allocate enough memory.
        //
        // Bit numbers  7-3         2-0
        // Field name   Exponent    Mantissa"
        u8 window_descriptor = (u8)IO_read_bits(in, 8);
        u8 exponent = window_descriptor >> 3;
        u8 mantissa = window_descriptor & 7;

        // Use the algorithm from the specification to compute window size
        // https://github.com/facebook/zstd/blob/dev/doc/zstd_compression_format.md#window_descriptor
        size_t window_base = (size_t)1 << (10 + exponent);
        size_t window_add = (window_base / 8) * mantissa;
        header->window_size = window_base + window_add;
    }

    // decode dictionary id if it exists
    if (dictionary_id_flag) {
        // "This is a variable size field, which contains the ID of the
        // dictionary required to properly decode the frame. Note that this
        // field is optional. When it's not present, it's up to the caller to
        // make sure it uses the correct dictionary. Format is little-endian."
        const int bytes_array[] = {0, 1, 2, 4};
        const int bytes = bytes_array[dictionary_id_flag];

        header->dictionary_id = (u32)IO_read_bits(in, bytes * 8);
    } else {
        header->dictionary_id = 0;
    }

    // decode frame content size if it exists
    if (single_segment_flag || frame_content_size_flag) {
        // "This is the original (uncompressed) size. This information is
        // optional. The Field_Size is provided according to value of
        // Frame_Content_Size_flag. The Field_Size can be equal to 0 (not
        // present), 1, 2, 4 or 8 bytes. Format is little-endian."
        //
        // if frame_content_size_flag == 0 but single_segment_flag is set, we
        // still have a 1 byte field
        const int bytes_array[] = {1, 2, 4, 8};
        const int bytes = bytes_array[frame_content_size_flag];

        header->frame_content_size = IO_read_bits(in, bytes * 8);
        if (bytes == 2) {
            // "When Field_Size is 2, the offset of 256 is added."
            header->frame_content_size += 256;
        }
    } else {
        header->frame_content_size = 0;
    }

    if (single_segment_flag) {
        // "The Window_Descriptor byte is optional. It is absent when
        // Single_Segment_flag is set. In this case, the maximum back-reference
        // distance is the content size itself, which can be any value from 1 to
        // 2^64-1 bytes (16 EB)."
        header->window_size = header->frame_content_size;
    }
}