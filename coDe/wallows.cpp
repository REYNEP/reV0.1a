#include "2D_Quad.hh"
#include "2D_Image.hh"

#include "amGHOST_V.hh"
#include "KeyMiceInput/EK.hh"

#include "amVK_Instance.hh"
#include "amVK_Device.hh"
#include "amVK_RenderPass.hh"
#include "amVK_WI.hh"
#include "amVK_Sync.hh"
//#include "amVK_Pipeline.hh"

#include "amVK_RendererT1.hh"
#include "amGHOST_Decode.hh"


/**
 * TODO: CMake: 
 *    1. USE CMake FindPackage, Check, Use & Log that if Found
 *    2. If not found, try to find it in extern amVK Folder...
 *    3.    People Can Specify variables like <amVK_EXT_glslang>
 * 
 *    4. Detect if its a SOURCE Dir without BINARIES & LIB
 *    5.    if so, use the GLSLang_CMakeLists.cmake file
 *    6. FurthurMore, we can detect the needed HEADER files....
 * 
 *    7. On the amVK Drive folder, We should only provide the BINARIES & HEADERS
 *    8.    That means Maintaining the GLSLang_CMakeLists.cmake, locally here at my PC
 *    9. We can Make DEBUG / RELEASE different builds & Upload to drive....
 *    
 *   10. If still not found, REPORT amVK ERROR Report... & Directions to solve
 *    
 * TODO: SCons: Use that like Godot
 * TODO: meson: We are there... halfway
 * 
 * TODO:  amVK: Insntance::filter_SurfaceExts() improve.... support for xcb/xlib
 * TODO:  amVK: add 'konf' prefix to funcs thats called by konfigurieren()
 * TODO:  amVK: expose filter_SurfaceFormats... furthur through amVK_WI... + solve the TODOs
 */
int main(void) {
    amGHOST_Window *wOne = amG_SYS->create_window(":𝐫𝐞", 0, 0, 1280, 720);          //GHOST - Generic Handy Operating System Toolkit 👻
    amG_SYS->add_EventKonsument(&EK);                                               // EK   - Event Konsument. xD (German)
                                                                                    // Your own Function to process amGHOST Event (OS Events)
    amVK_InstanceMK2 *amVK = new amVK_InstanceMK2(true);                            // true: Debug Extensions
    amVK->Create_VkInstance();                                                      // Vulkan Extension Created
    // add_InstanceExt('VK_EXT_swapchain_colorspace')                               // Check amVK_Classes to see features/functions like this

    amVK_SurfaceMK2     *amVK_S = new amVK_SurfaceMK2(wOne->create_vulkan_surface(amVK->s_Instance));           // GHOST Creates VkSurface
    amVK_DeviceMK2      *amVK_D = new amVK_DeviceMK2(amVK_S->select_DisplayDevice(), 1, 0, amVK_DP_GRAPHICS);
    amVK_D->Create_VkDevice();
    amVK_D->Activate_Device();      // Now, it'll be okay if you dont pass amVK_D everywhere

    

    amVK_RenderPassMK2 *amVK_RP = new amVK_RenderPassMK2(amVK_S, amVK_D);           // Why the RenderPass separated?
    amVK_RP->Create_RenderPass();                                                   // To become a standard for ColorSpace infos 🎨

    amVK_WI_MK2        *amVK_WI = new amVK_WI_MK2(":𝐫𝐞", amVK_S, amVK_RP, amVK_D);  // WI    - Window Interface    [highly modifiable]
    amVK_WI->Create_Swapchain();                                                    // see the class header, Lots of features...
    amVK_WI->create_Attachments();                                                  // Attachments & Framebuffers....
    amVK_WI->create_Framebuffers();                                                 // Cool enough implementation for now [amVK_Array Used]



    amVK_GraphicsPipes *amVK_PS = new amVK_GraphicsPipes(amVK_RP, amVK_D);          // This is like a 'Pipe'Store... where you build PipeLines from
    amVK_PS->konfigurieren();                                                       // Basic Configuration.... Still Modifiable.... 😉
    
    Image2D::pipeline.Initialize(amVK_PS);                                          // TODO: HANDLE Destruction
    Image2D aQuad = Image2D();
    amGHOST_DEC_PNG IMG("amGHOST/reynep.png");                                      // uses WUFFs by google 🙃



    amVK_RD RD(amVK_D);                                                             // Soon, you will prolly need to rewrite this class
    VkViewport xD = {0, 0, amVK_WI->extent.width, amVK_WI->extent.height, 0, 1};

    while(true) {
        amG_SYS->process_events(true);                                              // amGHOST processed all events and puts in QUEUE
        if (amG_SYS->dispatch_events() == false) {                                  // Calls that 'EK' from line 2 for every event
            break;                                                                  // Your EK can return '-1'
        }                                                                           // If it does so... dispatch_events() return false

        RD.Render_BeginRecord(amVK_WI);                                             // 😄 You should check this out yourself 😉

        //if (i == 0) vkCmdCopyBufferToImage(RD.m_cmdBuf.BUF, B.BUFFER, I.IMG, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, )

        vkCmdSetViewport(RD.m_cmdBuf.BUF, 0, 1, &xD);
        aQuad.Draw(RD.m_cmdBuf.BUF, nullptr);                                       // This is more Like RenderKonsument....
                                                                                    // Like it isn't getting drawn RN
        
        RD.EndRecord_N_Submit();                                                    // This Too 😊
    }

    /** delete wOne, won't work. */
    amG_SYS->destroy_window(wOne);
    amG_SYS->dispose_system();                                                      // CLean Up 😝

    return 0;
}
