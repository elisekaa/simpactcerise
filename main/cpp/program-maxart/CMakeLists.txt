set(SRC
	eventstudystart.cpp
	eventstudystep.cpp
	eventstudyend.cpp
	eventmonitoring.cpp
	facilities.cpp
	maxartpopulation.cpp
	personimpl.cpp
	start.cpp
	)

add_executable(maxart
    ${SRC}
    $<TARGET_OBJECTS:common>
    $<TARGET_OBJECTS:core>
    $<TARGET_OBJECTS:mnrm>
    $<TARGET_OBJECTS:util>
)
target_link_libraries(maxart ${LIBS})

unset(SRC)