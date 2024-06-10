cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

include(FetchContent)
project(SPLERM VERSION 1.0.0 LANGUAGES CXX)

if(WIN32)
  # SonarLint support for CMake requires the following flag to be set on.
  #(see https://community.sonarsource.com/t/sonarlint-for-visual-studio-v4-38-support-cmake-projects/50127)
  set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

set (BUILD_SHARED_LIBS FALSE)

if(APPLE)
    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
    include_directories(${SFML_INCLUDE_DIRS})
else()
    # Linux or Windows
    cmake_policy(SET CMP0135 NEW) # This cmake_policy avoids warning by cmake when we fetch contents based on URL
    FetchContent_Declare(
    sfml
    URL https://github.com/SFML/SFML/archive/refs/tags/2.6.1.tar.gz
    )
    FetchContent_MakeAvailable(sfml)
endif()

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) # This cmake_policy avoids warning by cmake when we use pugixml
FetchContent_Declare(
    pugixml
    URL https://github.com/zeux/pugixml/releases/download/v1.14/pugixml-1.14.tar.gz
)

FetchContent_MakeAvailable(pugixml)

FetchContent_Declare(
    box2d
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG origin/main
)
FetchContent_MakeAvailable(box2d)


add_subdirectory(mainLauncher)
add_subdirectory(src)
# enable_testing() must be in the source directory root (see cmake documentation at https://cmake.org/cmake/help/latest/command/enable_testing.html)
# Otherwise, Visual Studio test explorer does not see unit tests (See ticket https://developercommunity.visualstudio.com/t/No-tests-discovered-for-googletest-and-C/1148799#T-ND1150621)
enable_testing()
add_subdirectory(unitTests)