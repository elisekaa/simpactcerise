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

add_library(maxart OBJECT ${SRC})

unset(SRC)
