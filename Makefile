INCS = Header.h expr.h catch.h parse.h val.h pointer.h
INCSTEST = exec.h
SRCS = main.cpp textHelp.cpp expr.cpp parse.cpp val.cpp
SRCSTEST = test_msdscript.cpp exec.cpp
msdscript: $(SRCS) $(INCS) ; c++ --std=c++14 -O2 -o msdscript $(SRCS)
test_msdscript: $(SRCSTEST) $(INCSTEST) ; c++ --std=c++14 -O2 -o test_msdscript $(SRCSTEST)
.PHONY: test
test: msdscript
	./msdscript --test
