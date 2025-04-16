set(MODEL_SOURCES
    WordModel.cpp
    WordModel.h
    GameModel.cpp
    GameModel.h
    WordEvaluator.cpp
    WordEvaluator.h
)

add_library(model STATIC ${MODEL_SOURCES})

target_link_libraries(model PUBLIC
    Qt6::Core
)

target_include_directories(model PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
) 