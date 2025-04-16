set(CONTROLLER_SOURCES
    GameController.cpp
    GameController.h
)

add_library(controller STATIC ${CONTROLLER_SOURCES})

target_link_libraries(controller PUBLIC
    model
    Qt6::Core
)

target_include_directories(controller PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
) 