#include "amVK_Pipeline.hh"

/** Dont create multiple pipelines.... from same shaders */
class Quad2D_Pipeline : public amVK_Pipeline {
    public:
    char *shader = "agents/2D_Quad"; 

    Quad2D_Pipeline() {}
    bool Initialize(amVK_GraphicsPipes *PS) {amVK_Pipeline::Build_4_Device(shader, PS); return true;}

    ~Quad2D_Pipeline() {}

    /** VkPipelineLayour is one of the minimum things that must be created.... thus ZEROs n NULLs*/
    void _set_ShaderInputs(VkPipelineLayout L = nullptr) {
        if (L) layout = L;
        else ShaderInputsMK2::set_Info(0, nullptr, 0, nullptr);
    }
};


/** Initialize the pipeline before using */
class Quad2D {
    public:
    static inline Quad2D_Pipeline pipeline;

    float mat4[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

     Quad2D() {}
    ~Quad2D() {}

    void Draw(VkCommandBuffer CMD) {
        vkCmdBindPipeline(CMD, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.P);
        vkCmdDraw(CMD, 6, 1, 0, 0);
    }
};