set(SRC
    eventmonitoring.cpp
	personimpl.cpp
	start.cpp
)

add_executable(cyan
	${SRC}
	$<TARGET_OBJECTS:common>
	$<TARGET_OBJECTS:core>
	$<TARGET_OBJECTS:mnrm>
	$<TARGET_OBJECTS:util>
)
target_link_libraries(cyan "${LIBS}")

unset(SRC)
