cmake_minimum_required(VERSION 3.18)
project(snayai)

find_package(Torch REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB SRC CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(snayai ${SRC})
target_link_libraries(snayai PRIVATE sfml-window sfml-system sfml-graphics "${TORCH_LIBRARIES}")
set_property(TARGET snayai PROPERTY CXX_STANDARD 17)

target_include_directories(snayai PUBLIC
  src
  include
)

if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET snayai
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:snayai>)
endif (MSVC)