#include "amGHOST_V.hh"

int EK(amGHOST_Event *event) {  /** EventKonsument */
    if (event->m_type == amGHOST_kWindowClose) {
        return -1;              /** dispatch_events() will stop immediately, & return false */
    }
    return 0;
}
