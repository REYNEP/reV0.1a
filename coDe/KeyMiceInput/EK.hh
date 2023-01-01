#include "amGHOST_V.hh"

/** \param window_userData: TYPE: amVK_WI_MK2 */
void fn_WindowResized(void *window_userData);

int EK(amGHOST_Event *event) {          /** EventKonsument */
    switch (event->m_type) 
    {
        case amGHOST_kWindowClose:
            return -1;                  /** dispatch_events() will stop immediately, & return false */
        case amGHOST_kWindowResized:
            fn_WindowResized(event->m_win->window_userData);
    }
    return 0;
}

#ifdef WALLOWS
    #include "amVK_WI.hh"

    /** Will it really be bad if we like have it inside the EK instead.... I mean after all that was the point of creating that EK thingy */
    void fn_WindowResized(void *window_userData) {
        amVK_WI_MK2 *WI = reinterpret_cast<amVK_WI_MK2 *> (window_userData);
        if (WI == nullptr) {amVK_LOG_EX("amGHOST_Window::window_userData == nullptr");}
        WI->CleanUp_Swapchain();
        WI->Create_Swapchain();
        WI->create_Attachments();
        WI->create_Framebuffers();
    }
#endif