cmake_minimum_required(VERSION 3.22)

project(mavsdk-bug)
set(CMAKE_CXX_STANDARD 20)

if(BUILD_OFFLINE)
    message(STATUS "****BUILDING OFFLINE****")
    set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
endif()

include(FetchContent)

FetchContent_Declare(
    cmake-require-content
    GIT_REPOSITORY "https://github.com/weagle08/cmake-require-content.git"
    GIT_TAG "main"
)
FetchContent_MakeAvailable(cmake-require-content)

include(RequireContent)

add_compile_definitions(DEBUG)

set(BUILD_TESTS OFF)
set(BUILD_SHARED_LIBS OFF)
RequireContent(
    mavsdk
    GIT_REPOSITORY "https://github.com/mavlink/MAVSDK.git"
    GIT_TAG "v1.4.7"
)

include(AddExecutable)
executable(
    ${CMAKE_PROJECT_NAME}
    "src/main.cpp"
)

target_include_directories(
    ${CMAKE_PROJECT_NAME} PRIVATE
    ${mavsdk_SOURCE_DIR}/plugins # documentation says i should be able to add something like mavsdk_[plugin] to my link libraries but doesn't seem to work with local build vs global shared
    ${mavsdk_BINARY_DIR}/third_party/mavlink/mavlink/src/mavlink/include # unfortunately the mavlink passthrough plugin is expecting mavlink on a specific path
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME} PRIVATE
    mavsdk
)