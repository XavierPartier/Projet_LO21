QT += widgets
QT += xml

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

SOURCES += \
    main.cpp \
    calendarview.cpp \
    timing.cpp \
    calendar.cpp \
    projectview.cpp \
    mainview.cpp

HEADERS += \
    calendarview.h \
    timing.h \
    calendar.h \
    projectview.h \
    mainview.h
