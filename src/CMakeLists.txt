add_subdirectory(model)
add_subdirectory(controller)
add_subdirectory(view)

set(MAIN_SOURCES
    main.cpp
)

add_executable(wordle ${MAIN_SOURCES})

target_link_libraries(wordle PRIVATE
    model
    controller
    Qt6::Core
    Qt6::Quick
)

target_sources(wordle PRIVATE
    ${CMAKE_SOURCE_DIR}/qml.qrc
)

add_custom_command(TARGET wordle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/WORDS
    ${CMAKE_CURRENT_BINARY_DIR}/WORDS
) 