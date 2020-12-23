file(GLOB_RECURSE GENERATOR_HEADERS *.hpp)
file(GLOB_RECURSE GENERATOR_SOURCES *.cpp )

add_library(generator STATIC ${GENERATOR_SOURCES} ${GENERATOR_HEADERS})

target_link_libraries(generator PUBLIC glm)

target_include_directories(generator PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_compile_definitions(generator PUBLIC -DGENERATOR_USE_GLM -DGLM_ENABLE_EXPERIMENTAL)
