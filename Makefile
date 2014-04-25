# options du compilateur
CXX      = g++

CXXFLAGS = -Wall -I /usr/include/sfml-1.6 -iquote sources/includes -std=c++11 -lsfml-graphics-1.6 -lsfml-window-1.6 -lsfml-system-1.6
#CXXFLAGS = -Wall -iquote sources/includes -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system



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
	$(CXX) $(CXXFLAGS) -o $@ $^

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
$(cache)/%.o:		%.cc
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -Ofast -MMD -MF $(cache)/$*.d -c -o $@ $<

$(cache)/%.debug.o :	%.cc
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -g -MMD -MF $(cache)/$*.d -c -o $@ $<



# on inclut les fichiers de dépendances générés dans %.o
deps   = $(src_release:%.cc=$(cache)/%.d)
-include $(deps)



