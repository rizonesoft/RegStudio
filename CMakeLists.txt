cmake_minimum_required(VERSION 3.25)
project(RegStudio LANGUAGES CXX RC)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
set(RESOURCES "resources/resource.rc")

add_executable(RegStudio WIN32 ${SOURCES} ${RESOURCES})

# GCC Flags
# -municode: Use wWinMain (Unicode) entry point
# -static: Embed standard libraries (libgcc/libstdc++) into the exe
target_compile_options(RegStudio PRIVATE -municode -O3 -Wall)
target_link_options(RegStudio PRIVATE -municode -static -static-libgcc -static-libstdc++)

# Link Windows System Libraries
target_link_libraries(RegStudio PRIVATE 
    comctl32    # TreeView, ListView
    shlwapi     # Path helpers
    dwmapi      # Dark Mode API
    uxtheme     # Visual Styles (Explorer look)
    advapi32    # Registry API
)
