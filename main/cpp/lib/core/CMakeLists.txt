set(SRC
    parallel.h
    personaleventlist.cpp
    personaleventlisttesting.cpp
    personbase.cpp
    populationalgorithmadvanced.cpp
    populationalgorithmsimple.cpp
    populationalgorithmtesting.cpp
    populationevent.cpp
    populationinterfaces.h
    populationstateadvanced.cpp
    populationstatesimple.cpp
    populationstatesimpleadvancedcommon.cpp
    populationstatetesting.cpp
    populationutil.cpp
)

add_library(core ${SRC})


unset(SRC)