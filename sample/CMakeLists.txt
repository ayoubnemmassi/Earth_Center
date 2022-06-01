
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_executable(sample
  ${SOURCES}
  )

target_link_libraries(sample PUBLIC sfml-graphics)
add_custom_target(copy-Fonts ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Fonts)
# "COMMAND ${CMAKE_COMMAND} -E copy_directory" triggers a generation error with Visual Studio
# So we need to do  the following solution
file(GLOB RESOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/Fonts/*.*)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Fonts
                   DEPENDS ${CMAKE_SOURCE_DIR}/Fonts
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/Fonts
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           ${SOURCES}
                           ${CMAKE_CURRENT_BINARY_DIR}/Fonts)
add_dependencies(sample copy-Fonts)
add_custom_target(copy-Textures ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Textures)
# "COMMAND ${CMAKE_COMMAND} -E copy_directory" triggers a generation error with Visual Studio
# So we need to do  the following solution
file(GLOB RESOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/Textures/*.*)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Textures
                   DEPENDS ${CMAKE_SOURCE_DIR}/Textures
                   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/Textures
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                           ${SOURCES}
                           ${CMAKE_CURRENT_BINARY_DIR}/Textures)
add_dependencies(sample copy-Textures)