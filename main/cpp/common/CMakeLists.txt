set(SRC
#
    event/eventaidsmortality.cpp
    event/eventaidsstage.cpp
    event/eventbirth.cpp
    event/eventcheckstopalgorithm.cpp
    event/eventchronicstage.cpp
    event/eventconception.cpp
    event/eventdebut.cpp
    event/eventdiagnosis.cpp
    event/eventdissolution.cpp
    event/eventdropout.cpp
    event/eventformation.cpp
    event/eventhivseed.cpp
    event/eventhivtransmission.cpp
    event/eventhsv2seed.cpp
    event/eventhsv2transmission.cpp
    event/eventintervention.cpp
    event/eventmortality.cpp
    event/eventmortalitybase.cpp
    event/eventperiodiclogging.cpp
    event/eventrelocation.cpp
    event/eventseedbase.cpp
    event/eventsyncpopstats.cpp
    event/eventsyncrefyear.cpp
    event/eventvariablefiretime.h
    event/simpactevent.cpp
#
    pop/person.cpp
    pop/person_family.h
    pop/person_hiv.cpp
    pop/person_hsv2.cpp
    pop/person_relations.cpp
    pop/simpactpopulation.cpp
#
    AidsTimeOfDeathUtility.cpp
    coarsemap.cpp
    configsettingslog.cpp
    configutil.cpp
    evthazard.h
    evthazarddissolution.cpp
    evthazardformationagegap.cpp
    evthazardformationagegaprefyear.cpp
    evthazardformationsimple.cpp
    hazardfunctionformationagegap.cpp
    hazardfunctionformationagegaprefyear.cpp
    hazardfunctionformationsimple.cpp
    logsystem.cpp
    main.cpp
    main_hazardtest.cpp
    signalhandlers.cpp
    vspmodel.h
    vspmodellogdist.cpp
    vspmodellogweibullwithnoise.cpp
)

add_library(common_cyan OBJECT ${SRC})
target_include_directories(common_cyan PUBLIC ../cyan)

add_library(common_maxart OBJECT ${SRC})
target_include_directories(common_maxart PUBLIC ../maxart)

unset(SRC)
