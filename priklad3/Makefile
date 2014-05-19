SOURCES = iobrazec.cpp \
	asciikontext.cpp \
	ctverec.cpp \
	kruh.cpp \
	polygony.cpp \
	platno.cpp \
	trojuhelnik.cpp

test_SOURCES = $(SOURCES) \
	test.cpp

main_SOURCES = $(SOURCES) \
	main.cpp

CXX = g++
CXXFLAGS = -g -W -Wall -Werror -std=c++11
LDFLAGS = -g

test_OBJECTS = $(test_SOURCES:.cpp=.o)

main_OBJECTS = $(main_SOURCES:.cpp=.o)

all: test main

test: $(test_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

main: $(main_OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean::
	$(RM) test main

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
