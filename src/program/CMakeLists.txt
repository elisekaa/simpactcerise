set(SOURCES_SIMPACT
	personimpl.cpp
	start.cpp
	../program-common/coarsemap.cpp
	../program-common/person.cpp
	../program-common/person_relations.cpp
	../program-common/person_hiv.cpp
	../program-common/person_hsv2.cpp
	../program-common/logsystem.cpp
	../program-common/simpactpopulation.cpp
	../program-common/event/eventmortalitybase.cpp
	../program-common/event/eventmortality.cpp
	../program-common/event/eventaidsmortality.cpp
	../program-common/event/eventformation.cpp
	../program-common/event/eventdissolution.cpp
	../program-common/event/eventdebut.cpp
	../program-common/event/eventhivtransmission.cpp
	../program-common/event/eventhsv2transmission.cpp
	../program-common/event/eventchronicstage.cpp
	../program-common/event/eventseedbase.cpp
	../program-common/event/eventhivseed.cpp
	../program-common/event/eventhsv2seed.cpp
	../program-common/event/eventintervention.cpp
	../program-common/event/eventaidsstage.cpp
	../program-common/event/eventconception.cpp
	../program-common/event/eventbirth.cpp
	../program-common/event/eventdiagnosis.cpp
	../program-common/event/eventmonitoring.cpp
	../program-common/event/eventdropout.cpp
	../program-common/event/eventperiodiclogging.cpp
	../program-common/event/eventsyncpopstats.cpp
	../program-common/event/eventsyncrefyear.cpp
	../program-common/event/eventcheckstopalgorithm.cpp
	../program-common/event/eventrelocation.cpp
	../program-common/vspmodellogweibullwithnoise.cpp
	../program-common/vspmodellogdist.cpp
	../program-common/simpactevent.cpp
	../program-common/evthazardformationsimple.cpp
	../program-common/evthazardformationagegap.cpp
	../program-common/evthazardformationagegaprefyear.cpp
	../program-common/evthazarddissolution.cpp
	../program-common/hazardfunctionformationsimple.cpp
	../program-common/hazardfunctionformationagegap.cpp
	../program-common/hazardfunctionformationagegaprefyear.cpp
	../program-common/main_hazardtest.cpp
	../program-common/main.cpp
	../program-common/signalhandlers.cpp
	../program-common/configutil.cpp
	../program-common/aidstodutil.cpp
	../program-common/configsettingslog.cpp
	)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/../program-common/")
add_simpact_executable(simpact-cyan ${SOURCES_SIMPACT})
install_simpact_executable(simpact-cyan)


