list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

function(violet_lint)
  set(oneValueArgs TARGET)
  cmake_parse_arguments(VIOLET_LINT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  find_package(ClangTidy REQUIRED)

  if(VIOLET_FIX)
    set(fixFlag --fix)
  endif()

  if(VIOLET_WARNINGS_AS_ERRORS)
    set(werror --warnings-as-errors=*)
  endif()

  set(clangTidyCommand "${CLANG_TIDY_EXECUTABLE}" ${fixFlag} ${werror} --quiet)

  if(CMAKE_GENERATOR MATCHES "Makefiles" OR CMAKE_GENERATOR MATCHES "Ninja")
    set_property(TARGET ${VIOLET_LINT_TARGET} PROPERTY CXX_CLANG_TIDY ${clangTidyCommand})
  else()
    get_target_property(target_sources ${VIOLET_LINT_TARGET} SOURCES)
    get_target_property(sourceDir ${VIOLET_LINT_TARGET} SOURCE_DIR)

    foreach(source ${target_sources})
      if(NOT IS_ABSOLUTE "${source}")
        list(APPEND sources "${sourceDir}/${source}")
      else()
        list(APPEND sources "${source}")
      endif()
    endforeach()

    set(clangTidyIncludes
      ${CONAN_INCLUDE_DIRS}
      ${CONAN_INCLUDE_DIRS_DEBUG}
      ${CONAN_INCLUDE_DIRS_RELEASE}
      ${PROJECT_SOURCE_DIR}/include
    )
    list(TRANSFORM clangTidyIncludes PREPEND "-I")

    add_custom_command(TARGET ${VIOLET_LINT_TARGET} POST_BUILD
      COMMAND ${clangTidyCommand} ${sources} -- ${clangTidyIncludes}
    )
  endif()
endfunction()
