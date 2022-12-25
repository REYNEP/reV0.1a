# MODIFIED FILE.... [GLEW PART REMOVED]
#   Original: amGHOST/build_files/amGHOST_Variables.cmake
#   [Patched up with amVK]
#-----------------------------------------------------------------------------
set(VAR_VULKAN_DIR         ${CMAKE_SOURCE_DIR}/amVK/VK)
set(VAR_VULKAN_LIB_DIR     ${CMAKE_SOURCE_DIR}/amVK/extern/lib/Release)
set(VAR_amVK_LOGGER_N_UTIL ${CMAKE_SOURCE_DIR}/amVK/intern)
set(VAR_amVK_LOGGER_N_UTIL_IMPL FALSE)

include(build_help_funcs)

#-----------------------------------------------------------------------------
# amGHOST_VULKAN   [amGHOST_Window::vulkan_create_surface()]

  set(VAR_VULKAN_INC
    # include "vulkan/vulkan.h"
    ${VAR_VULKAN_DIR}/include
  )

  re_file_EXISTS(${VAR_VULKAN_INC}/vulkan/vulkan.h FATAL_ERROR)

if(WIN32)
  re_find_library(VAR_VULKAN_LIB
    # vulkan-1.lib comes with vulkan-sdk-lunarg
    NAMES
      vulkan
      vulkan-1    #On windows as of Vulkan 1.2
    PATHS
      ${VAR_VULKAN_LIB_DIR}
    NO_DEFAULT_PATH
    REQUIRED
    ERROR_MSG
      "Try running amVK/extern/download.py or see amVK/README"
  )
else()
  find_package(Vulkan REQUIRED)
  find_package(X11 REQUIRED)

  set(VAR_VULKAN_LIB Vulkan::Vulkan)
endif()