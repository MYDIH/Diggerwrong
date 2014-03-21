# options du compilateur
CXX      = g++
CXXFLAGS = -Wall -iquote sources/includes -std=c++11
debug    = 


# constantes
buildir  = Builds

# pour utiliser le globbing
SHELL    = /bin/bash -O extglob -O globstar -c



nonunit = $(shell source Objects.sh ; nonunit )
unit    = $(shell source Objects.sh ; unit    )




release:	$(nonunit)
	mkdir -p $(buildir)/release
	$(CXX) $(CXXFLAGS) -o $(buildir)/release/diggewrong $^

check-syntax:
	-$(CXX) $(CXXFLAGS) -fsyntax-only  ${CHK_SOURCES} # -o null


unit:		$(unit)
	mkdir -p $(buildir)/unit-tests
	$(CXX) $(CXXFLAGS) -o $(buildir)/unit-tests/diggewrong $^


test:		unit
	cd $(buildir)/unit-tests/ && ./diggewrong


debug:		$(nonunit) 
	mkdir -p $(buildir)/debug
	$(CXX) $(CXXFLAGS) -g -o $(buildir)/debug/diggewrong $^


clean:
	rm sources/**/*.o
	rm sources/**/*.d
	rm -r $(buildir)


# compilation + génération des fichiers de dépendance
%.o:		%.cc
	$(CXX) $(CXXFLAGS) $(debug) -MMD -MF $*.d -c -o $@ $<




# on inclut les fichiers de dépendances générés dans %.o
-include $(shell echo sources/**/*.d)

