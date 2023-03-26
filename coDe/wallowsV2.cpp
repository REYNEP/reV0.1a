#include "amGHOST_V.hh"
#include "KeyMiceInput/EK.hh"

/**
 * \todo
 */
int main(void) {
        /**     GHOST - Generic Handy Operating System Toolkit 👻      */
    amGHOST_Window* wOne = amG_SYS->create_window(":𝐫𝐞", 0, 0, 600, 600);
        /** [EK.hh]    EK   - Event Konsument. xD (German) 👀
            Your own Function to process amGHOST Event (OS Events)     */
    amG_SYS->add_EventKonsument(&EK_EX0);

    while (true) {	/** endless GameLoop haha */
            /**     amGHOST processed all events and puts in QUEUE     */
        amG_SYS->process_events(true);

            /**       Calls that 'EK' from line 2 for every event
             *                   Your EK can return '-1'
             *    If it does so... dispatch_events() return false 😄   */
        if (amG_SYS->dispatch_events() == false)
            break;
    }

    /** `delete wOne`      : won't work */
    amG_SYS->destroy_window(wOne);						   // CLean Up 😝
    amG_SYS->dispose_system();
}