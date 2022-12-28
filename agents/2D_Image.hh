#include "amVK_Pipeline.hh"
#include "amVK_Descriptors.hh"
#include "amVK_ImgNBuf.hh"

/** Don't create multiple pipelines.... from same shaders */
class Image2D_Pipeline : public amVK_Pipeline {
    public:
    char *shader = "agents/2D_Image";

    VkSampler _test = nullptr;
    VkDescriptorSetLayoutBinding Binding = {
        0,          /** Binding number in the shader */
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        1,          /** Number of Descriptors */
        VK_SHADER_STAGE_FRAGMENT_BIT,
        nullptr     /** you can create your own Sampler */
    };
    amVK_DSetLayout IMG_DSetLayout;

    /** \see DSetLayout Docs in amVK_Descriptors.hh */
    bool Initialize(amVK_GraphicsPipes *PS) {
        
        if (!IMG_DSetLayout.Create(PS->amVK_D, 1, &Binding)) {
            amVK_LOG_EX("[Image2D_Pipeline]:    amVK_DSetLayout.Create() failed....!");
        }

        amVK_Pipeline::Build_4_Device(shader, PS); 
        return true;
    }

     Image2D_Pipeline() {}
    ~Image2D_Pipeline() {}

    void _set_ShaderInputs(VkPipelineLayout L = nullptr) {
        if (L) layout = L;
        else ShaderInputsMK2::set_Info(0, nullptr, 1, &IMG_DSetLayout.L);
        /** Later VkPipelineLayout is created inside \fn Build_4_Device() */
    }
};

/** Initialize the pipeline before using */
class Image2D {
    public:
    static inline Image2D_Pipeline pipeline;
    static inline VkSampler Def_Sampler = nullptr;
    VkDescriptorSet DS;
    
    float mat4[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    Image2D() {}
   ~Image2D() {}

    /** You can set your own   VkSampler.... */
    void ReadyDS(amVK_DeadPool *DeadPool, BufferMK2 B, ImageMK2 I, bool UpdateOnly = false) {
        if (!UpdateOnly)
            DS = DeadPool->Allocate_Single(pipeline.IMG_DSetLayout.L);
        if (!Def_Sampler)
            Def_Sampler = ImageMK2::amvkCreateSampler(DeadPool->amVK_D);


        VkDescriptorBufferInfo BI = {
            B.BUFFER, B.m_sizeByte, B.m_memOffset
        };
        VkDescriptorImageInfo II = {
            Def_Sampler, I.VIEW, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
        };
        VkWriteDescriptorSet WriteSet = {VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, nullptr,
            DS,         /** dstSet */
            0, 0,       /** dstBinding, dstArrayElement */
            1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            &II, &BI, nullptr /** pImageInfo, pBufferInfo, pTexelBufferView */
        };
        vkUpdateDescriptorSets(DeadPool->amVK_D->D, 1, &WriteSet, 0, nullptr);
    }

    void Draw(VkCommandBuffer CMD) {
        const uint32_t offset = 0;
        vkCmdBindPipeline(CMD, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.P);
        vkCmdBindDescriptorSets(CMD, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.layout, 0, 1, &DS, 0, nullptr);
        vkCmdDraw(CMD, 6, 1, 0, 0);     // TriangleStrip
    }
};