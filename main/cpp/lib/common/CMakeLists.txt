set(SRC
    pop/person.cpp
    pop/person_relations.cpp
    pop/person_hiv.cpp
    pop/person_hsv2.cpp
    pop/simpactpopulation.cpp
#
    event/eventmortalitybase.cpp
    event/eventmortality.cpp
    event/eventaidsmortality.cpp
    event/eventformation.cpp
    event/eventdissolution.cpp
    event/eventdebut.cpp
    event/eventhivtransmission.cpp
    event/eventhsv2transmission.cpp
    event/eventchronicstage.cpp
    event/eventseedbase.cpp
    event/eventhivseed.cpp
    event/eventhsv2seed.cpp
    event/eventintervention.cpp
    event/eventaidsstage.cpp
    event/eventconception.cpp
    event/eventbirth.cpp
    event/eventdiagnosis.cpp
    event/eventdropout.cpp
    event/eventperiodiclogging.cpp
    event/eventsyncpopstats.cpp
    event/eventsyncrefyear.cpp
    event/eventcheckstopalgorithm.cpp
    event/eventrelocation.cpp
    event/simpactevent.cpp
#
    coarsemap.cpp
    logsystem.cpp
    vspmodellogweibullwithnoise.cpp
    vspmodellogdist.cpp
    evthazardformationsimple.cpp
    evthazardformationagegap.cpp
    evthazardformationagegaprefyear.cpp
    evthazarddissolution.cpp
    hazardfunctionformationsimple.cpp
    hazardfunctionformationagegap.cpp
    hazardfunctionformationagegaprefyear.cpp
    #!!!! This is not OK -- needs to change
    main_hazardtest.cpp
    main.cpp
    #
    signalhandlers.cpp
    configutil.cpp
    aidstodutil.cpp
    configsettingslog.cpp
)

add_library(common ${SRC})


unset(SRC)
