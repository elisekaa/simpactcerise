set(SRC
    algorithm.cpp
    ExitStatus.cpp
    Event.cpp
    gslrandomnumbergenerator.cpp
    simplealgorithm.cpp
    State.cpp
)

add_library(mnrm OBJECT ${SRC})


unset(SRC)
