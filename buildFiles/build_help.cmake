include(build_help_funcs)

# amGHOST -----------
re_SubModule_EXISTS("amGHOST" "amGHOST/amGHOST_V.hh")

# amVK --------------
re_SubModule_EXISTS("amVK"    "amVK/amVK_Device.hh")
re_SubModule_EXISTS("amVK/VK" "amVK/VK/include/vulkan/vulkan.h")

# STOP, Obstacles Ahead!
if (NOT ${re_SubModule})
  message(STATUS "    try: `git submodule update --recursive --init`")  # `git submodule update --init` should work too... ig
  message(STATUS "     or: make.py")
  message(FATAL_ERROR "[:re] Stopping CMake....")
endif()
