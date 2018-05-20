add_executable(simpact_maxart
    main.cpp
    $<TARGET_OBJECTS:common_maxart>
    $<TARGET_OBJECTS:core>
    $<TARGET_OBJECTS:maxart>
    $<TARGET_OBJECTS:mnrm>
    $<TARGET_OBJECTS:util>
)
target_link_libraries(simpact_maxart ${LIBS})

add_executable(simpact_cyan
    main.cpp
    $<TARGET_OBJECTS:common_cyan>
    $<TARGET_OBJECTS:cyan>
    $<TARGET_OBJECTS:core>
    $<TARGET_OBJECTS:mnrm>
    $<TARGET_OBJECTS:util>
)
target_link_libraries(simpact_cyan "${LIBS}")