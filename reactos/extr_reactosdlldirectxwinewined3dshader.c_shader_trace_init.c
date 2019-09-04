#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_19__ ;
typedef  struct TYPE_27__   TYPE_17__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct wined3d_string_buffer {char* buffer; } ;
struct wined3d_shader_version {int type; int major; int /*<<< orphan*/  minor; } ;
struct TYPE_25__ {int /*<<< orphan*/  w; int /*<<< orphan*/  v; int /*<<< orphan*/  u; } ;
struct TYPE_22__ {TYPE_11__* idx; int /*<<< orphan*/  type; } ;
struct TYPE_27__ {TYPE_12__ reg; } ;
struct TYPE_37__ {int /*<<< orphan*/  byte_stride; TYPE_17__ reg; } ;
struct TYPE_36__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_35__ {int /*<<< orphan*/  structure_count; int /*<<< orphan*/  byte_stride; TYPE_17__ reg; } ;
struct TYPE_34__ {int /*<<< orphan*/  byte_count; TYPE_17__ reg; } ;
struct TYPE_33__ {int /*<<< orphan*/  body_count; int /*<<< orphan*/  array_size; int /*<<< orphan*/  index; } ;
struct TYPE_32__ {int /*<<< orphan*/  sysval_semantic; TYPE_17__ reg; } ;
struct TYPE_31__ {int /*<<< orphan*/  component_count; int /*<<< orphan*/  register_size; int /*<<< orphan*/  register_idx; } ;
struct TYPE_30__ {int /*<<< orphan*/  last_register; TYPE_17__ first_register; } ;
struct TYPE_23__ {int /*<<< orphan*/ * immconst_data; } ;
struct TYPE_24__ {TYPE_13__ u; } ;
struct TYPE_26__ {TYPE_14__ reg; } ;
struct TYPE_28__ {TYPE_17__ reg; } ;
struct TYPE_20__ {TYPE_9__ structured_resource; TYPE_17__ dst; TYPE_8__ thread_group_size; TYPE_7__ tgsm_structured; TYPE_6__ tgsm_raw; int /*<<< orphan*/  tessellator_partitioning; int /*<<< orphan*/  tessellator_output_primitive; int /*<<< orphan*/  tessellator_domain; int /*<<< orphan*/  count; TYPE_5__ fp; int /*<<< orphan*/  primitive_type; TYPE_4__ register_semantic; TYPE_3__ indexable_temp; TYPE_2__ index_range; TYPE_1__* icb; int /*<<< orphan*/  max_tessellation_factor; int /*<<< orphan*/  index; TYPE_16__ src; TYPE_19__ semantic; } ;
struct wined3d_shader_instruction {size_t handler_idx; int flags; int dst_count; int src_count; TYPE_16__* src; TYPE_17__* dst; TYPE_15__ texel_offset; scalar_t__ coissue; TYPE_16__* predicate; TYPE_10__ declaration; } ;
struct wined3d_shader_frontend {int /*<<< orphan*/  (* shader_read_instruction ) (void*,int const**,struct wined3d_shader_instruction*) ;int /*<<< orphan*/  (* shader_is_end ) (void*,int const**) ;int /*<<< orphan*/  (* shader_read_header ) (void*,int const**,struct wined3d_shader_version*) ;} ;
struct TYPE_29__ {int vec4_count; int /*<<< orphan*/ * data; } ;
struct TYPE_21__ {int /*<<< orphan*/  offset; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 size_t WINED3DSIH_BREAKC ; 
 size_t WINED3DSIH_BREAKP ; 
 size_t WINED3DSIH_CONTINUEP ; 
 size_t WINED3DSIH_DCL ; 
 size_t WINED3DSIH_DCL_CONSTANT_BUFFER ; 
 size_t WINED3DSIH_DCL_FUNCTION_BODY ; 
 size_t WINED3DSIH_DCL_FUNCTION_TABLE ; 
 size_t WINED3DSIH_DCL_GLOBAL_FLAGS ; 
 size_t WINED3DSIH_DCL_GS_INSTANCES ; 
 size_t WINED3DSIH_DCL_HS_FORK_PHASE_INSTANCE_COUNT ; 
 size_t WINED3DSIH_DCL_HS_JOIN_PHASE_INSTANCE_COUNT ; 
 size_t WINED3DSIH_DCL_HS_MAX_TESSFACTOR ; 
 size_t WINED3DSIH_DCL_IMMEDIATE_CONSTANT_BUFFER ; 
 size_t WINED3DSIH_DCL_INDEXABLE_TEMP ; 
 size_t WINED3DSIH_DCL_INDEX_RANGE ; 
 size_t WINED3DSIH_DCL_INPUT ; 
 size_t WINED3DSIH_DCL_INPUT_CONTROL_POINT_COUNT ; 
 size_t WINED3DSIH_DCL_INPUT_PRIMITIVE ; 
 size_t WINED3DSIH_DCL_INPUT_PS ; 
 size_t WINED3DSIH_DCL_INPUT_PS_SGV ; 
 size_t WINED3DSIH_DCL_INPUT_PS_SIV ; 
 size_t WINED3DSIH_DCL_INPUT_SGV ; 
 size_t WINED3DSIH_DCL_INPUT_SIV ; 
 size_t WINED3DSIH_DCL_INTERFACE ; 
 size_t WINED3DSIH_DCL_OUTPUT ; 
 size_t WINED3DSIH_DCL_OUTPUT_CONTROL_POINT_COUNT ; 
 size_t WINED3DSIH_DCL_OUTPUT_SIV ; 
 size_t WINED3DSIH_DCL_OUTPUT_TOPOLOGY ; 
 size_t WINED3DSIH_DCL_RESOURCE_RAW ; 
 size_t WINED3DSIH_DCL_RESOURCE_STRUCTURED ; 
 size_t WINED3DSIH_DCL_SAMPLER ; 
 size_t WINED3DSIH_DCL_TEMPS ; 
 size_t WINED3DSIH_DCL_TESSELLATOR_DOMAIN ; 
 size_t WINED3DSIH_DCL_TESSELLATOR_OUTPUT_PRIMITIVE ; 
 size_t WINED3DSIH_DCL_TESSELLATOR_PARTITIONING ; 
 size_t WINED3DSIH_DCL_TGSM_RAW ; 
 size_t WINED3DSIH_DCL_TGSM_STRUCTURED ; 
 size_t WINED3DSIH_DCL_THREAD_GROUP ; 
 size_t WINED3DSIH_DCL_UAV_RAW ; 
 size_t WINED3DSIH_DCL_UAV_STRUCTURED ; 
 size_t WINED3DSIH_DCL_UAV_TYPED ; 
 size_t WINED3DSIH_DCL_VERTICES_OUT ; 
 size_t WINED3DSIH_DEF ; 
 size_t WINED3DSIH_DEFB ; 
 size_t WINED3DSIH_DEFI ; 
 size_t WINED3DSIH_IF ; 
 size_t WINED3DSIH_IFC ; 
 size_t WINED3DSIH_RESINFO ; 
 size_t WINED3DSIH_RETP ; 
 size_t WINED3DSIH_SAMPLE_INFO ; 
 size_t WINED3DSIH_SYNC ; 
 size_t WINED3DSIH_TABLE_SIZE ; 
 size_t WINED3DSIH_TEX ; 
 size_t WINED3DSIH_TEXKILL ; 
 int WINED3DSI_INDEXED_DYNAMIC ; 
#define  WINED3DSI_RESINFO_RCP_FLOAT 144 
#define  WINED3DSI_RESINFO_UINT 143 
 int WINED3DSI_SAMPLER_COMPARISON_MODE ; 
#define  WINED3DSI_SAMPLE_INFO_UINT 142 
 int WINED3DSI_TEXLD_PROJECT ; 
#define  WINED3D_SHADER_CONDITIONAL_OP_NZ 141 
#define  WINED3D_SHADER_CONDITIONAL_OP_Z 140 
#define  WINED3D_SHADER_REL_OP_EQ 139 
#define  WINED3D_SHADER_REL_OP_GE 138 
#define  WINED3D_SHADER_REL_OP_GT 137 
#define  WINED3D_SHADER_REL_OP_LE 136 
#define  WINED3D_SHADER_REL_OP_LT 135 
#define  WINED3D_SHADER_REL_OP_NE 134 
#define  WINED3D_SHADER_TYPE_COMPUTE 133 
#define  WINED3D_SHADER_TYPE_DOMAIN 132 
#define  WINED3D_SHADER_TYPE_GEOMETRY 131 
#define  WINED3D_SHADER_TYPE_HULL 130 
#define  WINED3D_SHADER_TYPE_PIXEL 129 
#define  WINED3D_SHADER_TYPE_VERTEX 128 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_dump_decl_usage (struct wined3d_string_buffer*,TYPE_19__*,int,struct wined3d_shader_version*) ; 
 int /*<<< orphan*/  shader_dump_dst_param (struct wined3d_string_buffer*,TYPE_17__*,struct wined3d_shader_version*) ; 
 int /*<<< orphan*/  shader_dump_global_flags (struct wined3d_string_buffer*,int) ; 
 int /*<<< orphan*/  shader_dump_ins_modifiers (struct wined3d_string_buffer*,TYPE_17__*) ; 
 int /*<<< orphan*/  shader_dump_interpolation_mode (struct wined3d_string_buffer*,int) ; 
 int /*<<< orphan*/  shader_dump_precise_flags (struct wined3d_string_buffer*,int) ; 
 int /*<<< orphan*/  shader_dump_primitive_type (struct wined3d_string_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_dump_shader_input_sysval_semantic (struct wined3d_string_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_dump_src_param (struct wined3d_string_buffer*,TYPE_16__*,struct wined3d_shader_version*) ; 
 int /*<<< orphan*/  shader_dump_sync_flags (struct wined3d_string_buffer*,int) ; 
 int /*<<< orphan*/  shader_dump_tessellator_domain (struct wined3d_string_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_dump_tessellator_output_primitive (struct wined3d_string_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_dump_tessellator_partitioning (struct wined3d_string_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_dump_uav_flags (struct wined3d_string_buffer*,int) ; 
 int /*<<< orphan*/  shader_get_float_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * shader_opcode_names ; 
 int /*<<< orphan*/  string_buffer_free (struct wined3d_string_buffer*) ; 
 int /*<<< orphan*/  string_buffer_init (struct wined3d_string_buffer*) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (void*,int const**,struct wined3d_shader_version*) ; 
 int /*<<< orphan*/  stub2 (void*,int const**) ; 
 int /*<<< orphan*/  stub3 (void*,int const**,struct wined3d_shader_instruction*) ; 
 scalar_t__ wined3d_shader_instruction_has_texel_offset (struct wined3d_shader_instruction*) ; 

__attribute__((used)) static void shader_trace_init(const struct wined3d_shader_frontend *fe, void *fe_data)
{
    struct wined3d_shader_version shader_version;
    struct wined3d_string_buffer buffer;
    const char *type_prefix;
    const char *p, *q;
    const DWORD *ptr;
    DWORD i;

    if (!string_buffer_init(&buffer))
    {
        ERR("Failed to initialize string buffer.\n");
        return;
    }

    fe->shader_read_header(fe_data, &ptr, &shader_version);

    TRACE("Parsing %p.\n", ptr);

    switch (shader_version.type)
    {
        case WINED3D_SHADER_TYPE_VERTEX:
            type_prefix = "vs";
            break;

        case WINED3D_SHADER_TYPE_HULL:
            type_prefix = "hs";
            break;

        case WINED3D_SHADER_TYPE_DOMAIN:
            type_prefix = "ds";
            break;

        case WINED3D_SHADER_TYPE_GEOMETRY:
            type_prefix = "gs";
            break;

        case WINED3D_SHADER_TYPE_PIXEL:
            type_prefix = "ps";
            break;

        case WINED3D_SHADER_TYPE_COMPUTE:
            type_prefix = "cs";
            break;

        default:
            FIXME("Unhandled shader type %#x.\n", shader_version.type);
            type_prefix = "unknown";
            break;
    }

    shader_addline(&buffer, "%s_%u_%u\n", type_prefix, shader_version.major, shader_version.minor);

    while (!fe->shader_is_end(fe_data, &ptr))
    {
        struct wined3d_shader_instruction ins;

        fe->shader_read_instruction(fe_data, &ptr, &ins);
        if (ins.handler_idx == WINED3DSIH_TABLE_SIZE)
        {
            WARN("Skipping unrecognized instruction.\n");
            shader_addline(&buffer, "<unrecognized instruction>\n");
            continue;
        }

        if (ins.handler_idx == WINED3DSIH_DCL || ins.handler_idx == WINED3DSIH_DCL_UAV_TYPED)
        {
            shader_dump_decl_usage(&buffer, &ins.declaration.semantic, ins.flags, &shader_version);
            shader_dump_ins_modifiers(&buffer, &ins.declaration.semantic.reg);
            shader_addline(&buffer, " ");
            shader_dump_dst_param(&buffer, &ins.declaration.semantic.reg, &shader_version);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_CONSTANT_BUFFER)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_src_param(&buffer, &ins.declaration.src, &shader_version);
            shader_addline(&buffer, ", %s",
                    ins.flags & WINED3DSI_INDEXED_DYNAMIC ? "dynamicIndexed" : "immediateIndexed");
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_FUNCTION_BODY)
        {
            shader_addline(&buffer, "%s fb%u",
                    shader_opcode_names[ins.handler_idx], ins.declaration.index);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_FUNCTION_TABLE)
        {
            shader_addline(&buffer, "%s ft%u = {...}",
                    shader_opcode_names[ins.handler_idx], ins.declaration.index);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_GLOBAL_FLAGS)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_global_flags(&buffer, ins.flags);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_HS_MAX_TESSFACTOR)
        {
            shader_addline(&buffer, "%s %.8e", shader_opcode_names[ins.handler_idx],
                    ins.declaration.max_tessellation_factor);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_IMMEDIATE_CONSTANT_BUFFER)
        {
            shader_addline(&buffer, "%s {\n", shader_opcode_names[ins.handler_idx]);
            for (i = 0; i < ins.declaration.icb->vec4_count; ++i)
            {
                shader_addline(&buffer, "    {0x%08x, 0x%08x, 0x%08x, 0x%08x},\n",
                        ins.declaration.icb->data[4 * i + 0],
                        ins.declaration.icb->data[4 * i + 1],
                        ins.declaration.icb->data[4 * i + 2],
                        ins.declaration.icb->data[4 * i + 3]);
            }
            shader_addline(&buffer, "}");
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_INDEX_RANGE)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_dst_param(&buffer, &ins.declaration.index_range.first_register, &shader_version);
            shader_addline(&buffer, " %u", ins.declaration.index_range.last_register);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_INDEXABLE_TEMP)
        {
            shader_addline(&buffer, "%s x[%u][%u], %u", shader_opcode_names[ins.handler_idx],
                    ins.declaration.indexable_temp.register_idx,
                    ins.declaration.indexable_temp.register_size,
                    ins.declaration.indexable_temp.component_count);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_INPUT_PS)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_interpolation_mode(&buffer, ins.flags);
            shader_addline(&buffer, " ");
            shader_dump_dst_param(&buffer, &ins.declaration.dst, &shader_version);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_INPUT_PS_SGV
                || ins.handler_idx == WINED3DSIH_DCL_INPUT_SGV
                || ins.handler_idx == WINED3DSIH_DCL_INPUT_SIV
                || ins.handler_idx == WINED3DSIH_DCL_OUTPUT_SIV)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_dst_param(&buffer, &ins.declaration.register_semantic.reg, &shader_version);
            shader_addline(&buffer, ", ");
            shader_dump_shader_input_sysval_semantic(&buffer, ins.declaration.register_semantic.sysval_semantic);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_INPUT_PS_SIV)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_interpolation_mode(&buffer, ins.flags);
            shader_addline(&buffer, " ");
            shader_dump_dst_param(&buffer, &ins.declaration.register_semantic.reg, &shader_version);
            shader_addline(&buffer, ", ");
            shader_dump_shader_input_sysval_semantic(&buffer, ins.declaration.register_semantic.sysval_semantic);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_INPUT
                || ins.handler_idx == WINED3DSIH_DCL_OUTPUT)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_dst_param(&buffer, &ins.declaration.dst, &shader_version);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_INPUT_PRIMITIVE
                || ins.handler_idx == WINED3DSIH_DCL_OUTPUT_TOPOLOGY)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_primitive_type(&buffer, &ins.declaration.primitive_type);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_INTERFACE)
        {
            shader_addline(&buffer, "%s fp[%u][%u][%u] = {...}",
                    shader_opcode_names[ins.handler_idx], ins.declaration.fp.index,
                    ins.declaration.fp.array_size, ins.declaration.fp.body_count);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_RESOURCE_RAW)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_dst_param(&buffer, &ins.declaration.dst, &shader_version);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_RESOURCE_STRUCTURED)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_dst_param(&buffer, &ins.declaration.structured_resource.reg, &shader_version);
            shader_addline(&buffer, ", %u", ins.declaration.structured_resource.byte_stride);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_SAMPLER)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_dst_param(&buffer, &ins.declaration.dst, &shader_version);
            if (ins.flags == WINED3DSI_SAMPLER_COMPARISON_MODE)
                shader_addline(&buffer, ", comparisonMode");
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_TEMPS
                || ins.handler_idx == WINED3DSIH_DCL_GS_INSTANCES
                || ins.handler_idx == WINED3DSIH_DCL_HS_FORK_PHASE_INSTANCE_COUNT
                || ins.handler_idx == WINED3DSIH_DCL_HS_JOIN_PHASE_INSTANCE_COUNT
                || ins.handler_idx == WINED3DSIH_DCL_INPUT_CONTROL_POINT_COUNT
                || ins.handler_idx == WINED3DSIH_DCL_OUTPUT_CONTROL_POINT_COUNT
                || ins.handler_idx == WINED3DSIH_DCL_VERTICES_OUT)
        {
            shader_addline(&buffer, "%s %u", shader_opcode_names[ins.handler_idx], ins.declaration.count);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_TESSELLATOR_DOMAIN)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_tessellator_domain(&buffer, ins.declaration.tessellator_domain);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_TESSELLATOR_OUTPUT_PRIMITIVE)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_tessellator_output_primitive(&buffer, ins.declaration.tessellator_output_primitive);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_TESSELLATOR_PARTITIONING)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_tessellator_partitioning(&buffer, ins.declaration.tessellator_partitioning);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_TGSM_RAW)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_dst_param(&buffer, &ins.declaration.tgsm_raw.reg, &shader_version);
            shader_addline(&buffer, ", %u", ins.declaration.tgsm_raw.byte_count);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_TGSM_STRUCTURED)
        {
            shader_addline(&buffer, "%s ", shader_opcode_names[ins.handler_idx]);
            shader_dump_dst_param(&buffer, &ins.declaration.tgsm_structured.reg, &shader_version);
            shader_addline(&buffer, ", %u, %u", ins.declaration.tgsm_structured.byte_stride,
                    ins.declaration.tgsm_structured.structure_count);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_THREAD_GROUP)
        {
            shader_addline(&buffer, "%s %u, %u, %u", shader_opcode_names[ins.handler_idx],
                    ins.declaration.thread_group_size.x,
                    ins.declaration.thread_group_size.y,
                    ins.declaration.thread_group_size.z);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_UAV_RAW)
        {
            shader_addline(&buffer, "%s", shader_opcode_names[ins.handler_idx]);
            shader_dump_uav_flags(&buffer, ins.flags);
            shader_addline(&buffer, " ");
            shader_dump_dst_param(&buffer, &ins.declaration.dst, &shader_version);
        }
        else if (ins.handler_idx == WINED3DSIH_DCL_UAV_STRUCTURED)
        {
            shader_addline(&buffer, "%s", shader_opcode_names[ins.handler_idx]);
            shader_dump_uav_flags(&buffer, ins.flags);
            shader_addline(&buffer, " ");
            shader_dump_dst_param(&buffer, &ins.declaration.structured_resource.reg, &shader_version);
            shader_addline(&buffer, ", %u", ins.declaration.structured_resource.byte_stride);
        }
        else if (ins.handler_idx == WINED3DSIH_DEF)
        {
            shader_addline(&buffer, "def c%u = %.8e, %.8e, %.8e, %.8e", shader_get_float_offset(ins.dst[0].reg.type,
                    ins.dst[0].reg.idx[0].offset),
                    *(const float *)&ins.src[0].reg.u.immconst_data[0],
                    *(const float *)&ins.src[0].reg.u.immconst_data[1],
                    *(const float *)&ins.src[0].reg.u.immconst_data[2],
                    *(const float *)&ins.src[0].reg.u.immconst_data[3]);
        }
        else if (ins.handler_idx == WINED3DSIH_DEFI)
        {
            shader_addline(&buffer, "defi i%u = %d, %d, %d, %d", ins.dst[0].reg.idx[0].offset,
                    ins.src[0].reg.u.immconst_data[0],
                    ins.src[0].reg.u.immconst_data[1],
                    ins.src[0].reg.u.immconst_data[2],
                    ins.src[0].reg.u.immconst_data[3]);
        }
        else if (ins.handler_idx == WINED3DSIH_DEFB)
        {
            shader_addline(&buffer, "defb b%u = %s",
                    ins.dst[0].reg.idx[0].offset, ins.src[0].reg.u.immconst_data[0] ? "true" : "false");
        }
        else
        {
            if (ins.predicate)
            {
                shader_addline(&buffer, "(");
                shader_dump_src_param(&buffer, ins.predicate, &shader_version);
                shader_addline(&buffer, ") ");
            }

            /* PixWin marks instructions with the coissue flag with a '+' */
            if (ins.coissue)
                shader_addline(&buffer, "+");

            shader_addline(&buffer, "%s", shader_opcode_names[ins.handler_idx]);

            if (ins.handler_idx == WINED3DSIH_BREAKP
                    || ins.handler_idx == WINED3DSIH_CONTINUEP
                    || ins.handler_idx == WINED3DSIH_IF
                    || ins.handler_idx == WINED3DSIH_RETP
                    || ins.handler_idx == WINED3DSIH_TEXKILL)
            {
                switch (ins.flags)
                {
                    case WINED3D_SHADER_CONDITIONAL_OP_NZ: shader_addline(&buffer, "_nz"); break;
                    case WINED3D_SHADER_CONDITIONAL_OP_Z:  shader_addline(&buffer, "_z"); break;
                    default: shader_addline(&buffer, "_unrecognized(%#x)", ins.flags); break;
                }
            }
            else if (ins.handler_idx == WINED3DSIH_IFC
                    || ins.handler_idx == WINED3DSIH_BREAKC)
            {
                switch (ins.flags)
                {
                    case WINED3D_SHADER_REL_OP_GT: shader_addline(&buffer, "_gt"); break;
                    case WINED3D_SHADER_REL_OP_EQ: shader_addline(&buffer, "_eq"); break;
                    case WINED3D_SHADER_REL_OP_GE: shader_addline(&buffer, "_ge"); break;
                    case WINED3D_SHADER_REL_OP_LT: shader_addline(&buffer, "_lt"); break;
                    case WINED3D_SHADER_REL_OP_NE: shader_addline(&buffer, "_ne"); break;
                    case WINED3D_SHADER_REL_OP_LE: shader_addline(&buffer, "_le"); break;
                    default: shader_addline(&buffer, "_(%u)", ins.flags);
                }
            }
            else if (ins.handler_idx == WINED3DSIH_TEX
                    && shader_version.major >= 2
                    && (ins.flags & WINED3DSI_TEXLD_PROJECT))
            {
                shader_addline(&buffer, "p");
            }
            else if (ins.handler_idx == WINED3DSIH_RESINFO && ins.flags)
            {
                switch (ins.flags)
                {
                    case WINED3DSI_RESINFO_RCP_FLOAT: shader_addline(&buffer, "_rcpFloat"); break;
                    case WINED3DSI_RESINFO_UINT: shader_addline(&buffer, "_uint"); break;
                    default: shader_addline(&buffer, "_unrecognized(%#x)", ins.flags);
                }
            }
            else if (ins.handler_idx == WINED3DSIH_SAMPLE_INFO && ins.flags)
            {
                switch (ins.flags)
                {
                    case WINED3DSI_SAMPLE_INFO_UINT: shader_addline(&buffer, "_uint"); break;
                    default: shader_addline(&buffer, "_unrecognized(%#x)", ins.flags);
                }
            }
            else if (ins.handler_idx == WINED3DSIH_SYNC)
            {
                shader_dump_sync_flags(&buffer, ins.flags);
            }
            else
            {
                shader_dump_precise_flags(&buffer, ins.flags);
            }

            if (wined3d_shader_instruction_has_texel_offset(&ins))
                shader_addline(&buffer, "(%d,%d,%d)", ins.texel_offset.u, ins.texel_offset.v, ins.texel_offset.w);

            for (i = 0; i < ins.dst_count; ++i)
            {
                shader_dump_ins_modifiers(&buffer, &ins.dst[i]);
                shader_addline(&buffer, !i ? " " : ", ");
                shader_dump_dst_param(&buffer, &ins.dst[i], &shader_version);
            }

            /* Other source tokens */
            for (i = ins.dst_count; i < (ins.dst_count + ins.src_count); ++i)
            {
                shader_addline(&buffer, !i ? " " : ", ");
                shader_dump_src_param(&buffer, &ins.src[i - ins.dst_count], &shader_version);
            }
        }
        shader_addline(&buffer, "\n");
    }

    for (p = buffer.buffer; *p; p = q)
    {
        if (!(q = strstr(p, "\n")))
            q = p + strlen(p);
        else
            ++q;
        TRACE("    %.*s", (int)(q - p), p);
    }

    string_buffer_free(&buffer);
}