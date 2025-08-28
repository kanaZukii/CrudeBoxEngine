# Editor/CMakeLists.txt

add_executable(CrudeBoxEditor
    src/Main.cpp
)

# Link to your engine library (which already links glad, glfw, etc.)
target_link_libraries(CrudeBoxEditor PRIVATE CrudeBoxEngine)

# Optional: include editor-specific headers or ImGui directly (if needed)
target_include_directories(CrudeBoxEditor PRIVATE
    ${CMAKE_SOURCE_DIR}/extern/imgui
)
