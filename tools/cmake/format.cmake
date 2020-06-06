list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

function(violet_format)
  set(multiValueArgs SOURCES)
  cmake_parse_arguments(VIOLET_FORMAT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  find_package(ClangFormat REQUIRED)

  if (VIOLET_WARNINGS_AS_ERRORS)
    set(werror -Werror)
  endif()

  if(VIOLET_FIX)
    add_custom_command(TARGET violet PRE_BUILD
      COMMAND ${CLANG_FORMAT_EXECUTABLE} -i ${VIOLET_FORMAT_SOURCES}
    )
  else()
    add_custom_command(TARGET violet PRE_BUILD
      COMMAND ${CLANG_FORMAT_EXECUTABLE} ${werror} --dry-run ${VIOLET_FORMAT_SOURCES}
    )
  endif()
endfunction()
