set(SRC
    eventmonitoring.cpp
	personimpl.cpp
	start.cpp
)

add_library(cyan OBJECT ${SRC})

unset(SRC)
