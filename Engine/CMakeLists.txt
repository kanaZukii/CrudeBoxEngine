# Create the engine library
file(GLOB_RECURSE ENGINE_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(CrudeBoxEngine STATIC ${ENGINE_SOURCES})

target_include_directories(CrudeBoxEngine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Include paths (for headers)
target_include_directories(CrudeBoxEngine PUBLIC
    include
    ${CMAKE_SOURCE_DIR}/extern/glad/include
    ${CMAKE_SOURCE_DIR}/extern/glfw/include
    ${CMAKE_SOURCE_DIR}/extern/imgui
    ${CMAKE_SOURCE_DIR}/extern/glm
    ${CMAKE_SOURCE_DIR}/extern/stb
    ${CMAKE_SOURCE_DIR}/extern/openal-soft/include
)

# Link the libraries the engine needs
target_link_libraries(CrudeBoxEngine
    glad
    glfw
    imgui
    OpenAL
)

