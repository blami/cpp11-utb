SOURCES = databaze.cpp \
	json.cpp \
	predmet.cpp \
	skola.cpp \
	student.cpp \
	zapis.cpp

CXX = g++
CXXFLAGS = -g -W -Wall -Werror -std=c++11
LDFLAGS = -g

OBJECTS = $(SOURCES:.cpp=.o)

all: skola

skola: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean::
	$(RM) skola

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
