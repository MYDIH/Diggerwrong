# options du compilateur
CXX      = g++

CXXFLAGS = -Wall -iquote sources/includes -std=c++11 -I /usr/include/sfml-1.6

LDLIBS =   -lsfml-graphics-1.6 -lsfml-window-1.6 -lsfml-system-1.6
#LDLIBS =  -lsfml-graphics -lsfml-window -lsfml-system


# constantes
buildir = Builds
cache   = $(buildir)/.cache
bin     = diggewrong

# pour utiliser le globbing
SHELL    = /bin/bash -O extglob -O globstar -c

# recherche des sources
src_release = $(shell echo sources/**/!(unit|*.unit).cc)
src_unit    = $(shell echo sources/**/!(main).cc)
unit    = $(src_unit:%.cc=$(cache)/%.o)
release = $(src_release:%.cc=$(cache)/%.o)
debug   = $(src_release:%.cc=$(cache)/%.debug.o)



release:	$(buildir)/release/$(bin)
unit:		$(buildir)/unit/testsuite
debug:		$(buildir)/debug/$(bin)


$(buildir)/release/$(bin):	$(release)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o $@ $^

$(buildir)/unit/testsuite:		$(unit)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDLIBS) -lboost_unit_test_framework -o $@ $^

$(buildir)/debug/$(bin):	$(debug)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDLIBS) -g -o $@ $^

clean:
	-rm -r $(buildir)

test:		unit
	cd $(buildir)/unit/ && ./testsuite

check-syntax:
	-$(CXX) $(CXXFLAGS) -fsyntax-only  ${CHK_SOURCES}


# compilation + génération des fichiers de dépendance
$(cache)/%.o:		%.cc
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -O3 -MMD -MF $(cache)/$*.d -c -o $@ $<

$(cache)/%.debug.o :	%.cc
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -g -MMD -MF $(cache)/$*.d -c -o $@ $<



# on inclut les fichiers de dépendances générés dans %.o
deps   = $(src_release:%.cc=$(cache)/%.d)
-include $(deps)



