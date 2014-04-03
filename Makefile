# options du compilateur
CXX      = g++
CXXFLAGS = -Wall -iquote sources/includes -std=c++11

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
unit:		$(buildir)/unit/$(bin)
debug:		$(buildir)/debug/$(bin)

$(buildir)/release/$(bin):	$(release)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(buildir)/unit/$(bin):		$(unit)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -lboost_unit_test_framework -o $@ $^

$(buildir)/debug/$(bin):	$(debug)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -g -o $@ $^

clean:
	-rm -r $(buildir)

test:		unit
	cd $(buildir)/unit/ && ./$(bin)

check-syntax:
	-$(CXX) $(CXXFLAGS) -fsyntax-only  ${CHK_SOURCES}


# compilation + génération des fichiers de dépendance
Builds/.cache/%.o:		%.cc
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MF $@.d -c -o $@ $<

Builds/.cache/%.debug.o :	%.cc
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -g -MMD -MF $@.d -c -o $@ $<


# on inclut les fichiers de dépendances générés dans %.o
-include $(shell echo $(cache)/**/*.d)



