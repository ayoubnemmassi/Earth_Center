﻿
add_executable(mainLauncher mainLauncher.cpp)
if(WIN32)
   file(GLOB_RECURSE DYNAMIC_LIBS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/lib_openal32/${ARCH}/*.dll)
   file(COPY ${DYNAMIC_LIBS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
target_link_libraries(mainLauncher PUBLIC src pugixml sfml-graphics sfml-audio tmxlite sfml-system)

#add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources)
file(GLOB RESOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/resources/*.*)
file(GLOB RESOURCES_TEXTURES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/resources/Textures/*.*)
file(GLOB RESOURCES_FONTS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/resources/Fonts/*.*)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources
                   DEPENDS ${CMAKE_SOURCE_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/resources/Textures
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/resources/Fonts
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           ${RESOURCES}
                           ${CMAKE_CURRENT_BINARY_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           ${RESOURCES_TEXTURES}
                           ${CMAKE_CURRENT_BINARY_DIR}/resources/Textures
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           ${RESOURCES_FONTS}
                           ${CMAKE_CURRENT_BINARY_DIR}/resources/Fonts
                           )
add_dependencies(mainLauncher copy-resources)