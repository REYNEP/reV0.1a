set(  re_SubModule TRUE)
macro(re_SubModule_EXISTS
  module_name
  file
)

  if (NOT EXISTS ${CMAKE_SOURCE_DIR}/${file})
    message(STATUS "\n${module_name} [GIT SubModule] doesn't seem to be there.\n")
    set(re_SubModule FALSE)
  endif()

endmacro()



macro(re_file_EXISTS
  file_name
  msg_type
)

  if (NOT EXISTS ${file_name})
    message(${msg_type} "\n${file_name} doesn't seem to be there.\n")
  endif()

endmacro()





# param 'REQUIRED': Doesn't depend on CMake 3.18....
function(re_find_library
  OutVar
)

  cmake_parse_arguments(
    PARSE_ARGV 1                        # escapes 1st argument
    PARAM                               # pREFIX
    
    "NO_DEFAULT_PATH;REQUIRED"          # Options, a.k.a BOOL
    #""
    "ERROR_MSG;STATUS_MSG;FIXING_MSG"   # 1-Value
    "NAMES;PATHS;PATH_SUFFIXES"         # Multiple Values....
  )

  set(_NO_DEFAULT_PATH_)
  set(_REQUIRED_)

  if (${PARAM_NO_DEFAULT_PATH})
    set(_NO_DEFAULT_PATH_ "NO_DEFAULT_PATH")
  endif()

  find_library(_temp_
    NAMES
      ${PARAM_NAMES}
    PATHS
      ${PARAM_PATHS}
    PATH_SUFFIXES
      ${PARAM_PATH_SUFFIXES}
    ${_NO_DEFAULT_PATH_}
  )

  if (NOT EXISTS ${_temp_})
    message(NOTICE)
    message(STATUS "[re] Can't find '${PARAM_NAMES}' in ${PARAM_PATHS}\n")

    if (${PARAM_REQUIRED})
      message(SEND_ERROR ${PARAM_ERROR_MSG})
    endif()
  endif()

  set(${OutVar} ${_temp_} PARENT_SCOPE)
  unset(_temp_ CACHE)

endfunction()
