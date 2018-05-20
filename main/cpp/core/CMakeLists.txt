set(SRC
    GlobalEventDummy.h
    parallel.h
    personaleventlist.cpp
    personaleventlisttesting.cpp
    PersonAlgorithmInfo.h
    personbase.cpp
    PopulationAlgorithmAboutToFireInterface.h
    populationalgorithmadvanced.cpp
    PopulationAlgorithmInterface.h
    populationalgorithmsimple.cpp
    populationalgorithmtesting.cpp
    populationevent.cpp
    populationstateadvanced.cpp
    PopulationStateExtra.h
    PopulationStateInterface.h
    populationstatesimple.cpp
    populationstatesimpleadvancedcommon.cpp
    populationstatetesting.cpp
    populationutil.cpp
)

add_library(core OBJECT ${SRC})

unset(SRC)
