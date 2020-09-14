list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

function(violet_format)
  set(oneValueArgs TARGET)
  set(multiValueArgs SOURCES)
  cmake_parse_arguments(VIOLET_FORMAT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  find_program(clangFormat clang-format REQUIRED)

  if (VIOLET_WARNINGS_AS_ERRORS)
    set(werror -Werror)
  endif()

  if(VIOLET_FIX)
    add_custom_command(TARGET ${VIOLET_FORMAT_TARGET} PRE_BUILD
      COMMAND "${clangFormat}" -i ${VIOLET_FORMAT_SOURCES}
    )
  else()
    add_custom_command(TARGET ${VIOLET_FORMAT_TARGET} PRE_BUILD
      COMMAND "${clangFormat}" ${werror} --dry-run ${VIOLET_FORMAT_SOURCES}
    )
  endif()
endfunction()
