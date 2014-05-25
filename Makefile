# options du compilateur
CXX      = g++

CXXFLAGS = -Wall -iquote sources/includes -std=c++11 -I /usr/include/sfml-1.6

#LDLIBS =  -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lboost_program_options
LDLIBS =  -lsfml-audio-1.6 -lsfml-graphics-1.6 -lsfml-window-1.6 -lsfml-system-1.6 -lboost_program_options


# constantes
buildir = Builds
cache   = $(buildir)/.cache
bin     = diggewrong
rev     = $(shell git rev-list --count HEAD || echo '?')

# pour utiliser le globbing
SHELL    = /bin/bash -O extglob -O globstar -c

# recherche des sources
src_release = $(shell echo sources/**/!(.*|unit|*.unit|*_flymake).cc)
src_unit    = $(shell echo sources/**/!(.*|main|*_flymake).cc)

unit    = $(src_unit:%.cc=$(cache)/%.o)
release = $(src_release:%.cc=$(cache)/%.o)
debug   = $(src_release:%.cc=$(cache)/%.debug.o)



release:	$(buildir)/release/$(bin)
debug:		$(buildir)/debug/$(bin)
unit:		$(buildir)/unit/testsuite
pack:		$(buildir)/$(bin).tar.bz2
packsrc:	$(buildir)/$(bin)-src.tar.bz2


$(buildir)/release/$(bin):	$(release)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o $@ $^
	-ln -s ../../data/themes $(@D)

$(buildir)/debug/$(bin):	$(debug)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDLIBS) -g -o $@ $^
	-ln -s ../../data/themes $(@D)

$(buildir)/unit/testsuite:		$(unit)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDLIBS) -lboost_unit_test_framework -o $@ $^
	-ln -s ../../data/themes $(@D)

$(buildir)/$(bin).tar.bz2: $(buildir)/release/$(bin)
	mkdir -p $(@D)
	-rm -r                       /tmp/$(bin).makebuild/$(bin)/
	mkdir -p                     /tmp/$(bin).makebuild/$(bin)/
	cp $(buildir)/release/$(bin) /tmp/$(bin).makebuild/$(bin)/
	cp -r data/themes            /tmp/$(bin).makebuild/$(bin)/
	cd /tmp/$(bin).makebuild/ && tar -caf $(bin).tar.bz2 $(bin)
	cp /tmp/$(bin).makebuild/$(bin).tar.bz2 $@

$(buildir)/$(bin)-src.tar.bz2:
	mkdir -p $(@D)
	-rm -r                   /tmp/$(bin).makebuild/$(bin)-src/
	mkdir -p                 /tmp/$(bin).makebuild/$(bin)-src/data/themes
	cp -r !($(buildir)|data) /tmp/$(bin).makebuild/$(bin)-src/
	cp -r data/themes        /tmp/$(bin).makebuild/$(bin)-src/data/themes
	cd /tmp/$(bin).makebuild/ && tar -caf $(bin)-src.tar.bz2 $(bin)-src
	cp /tmp/$(bin).makebuild/$(bin)-src.tar.bz2 $@


clean:
	-rm -r $(buildir)

test:		unit
	cd $(buildir)/unit/ && ./testsuite

check-syntax:
	-$(CXX) $(CXXFLAGS) -fsyntax-only  ${CHK_SOURCES}

run: release
	cd $(buildir)/release && ./$(bin)



# compilation + génération des fichiers de dépendance
$(cache)/%.o:		%.cc
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -D REV=\"$(rev)\" -O3 -MMD -MF $(cache)/$*.d -c -o $@ $<

$(cache)/%.debug.o :	%.cc
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -D REV=\"$(rev)\" -g -MMD -MF $(cache)/$*.d -c -o $@ $<



# on inclut les fichiers de dépendances générés dans %.o
deps   = $(src_release:%.cc=$(cache)/%.d)
-include $(deps)



