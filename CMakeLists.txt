cmake_minimum_required(VERSION 3.4)
project(AZS)
include_directories("desktop/include")
if (MSVC)
link_directories("desktop/lib")
else()
link_directories("desktop/bin/linux")
endif()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} UltralightCore AppCore Ultralight WebCore)
if (APPLE)
  # Enable High-DPI on macOS through our custom Info.plist template
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in) 
endif()

if (MSVC)
  # Tell MSVC to use main instead of WinMain for Windows subsystem executables
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}"/desktop/bin/windows" $<TARGET_FILE_DIR:${PROJECT_NAME}>)  
 else()
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}"/desktop/bin/linux" $<TARGET_FILE_DIR:${PROJECT_NAME}>)  
endif()