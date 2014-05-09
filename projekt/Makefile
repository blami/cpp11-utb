SOURCES = databaze.cpp \
	json.cpp \
	menu.cpp \
	main.cpp \
	predmet.cpp \
	serializace.cpp \
	student.cpp \
	zapis.cpp \
	znamka.cpp

CXX = g++
CXXFLAGS = -g -W -Wall -Werror -std=c++11
LDFLAGS = -g

OBJECTS = $(SOURCES:.cpp=.o)

all: main

main: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean::
	$(RM) main

.cpp.o:
	$(CXX) -MD -MP $(CXXFLAGS) -o $@ -c $<

clean::
	$(RM) *.o

DEPENDS = $(SOURCES:.cpp=.d)

-include $(DEPENDS)

%.d:
	@touch $@

clean::
	$(RM) *.d
