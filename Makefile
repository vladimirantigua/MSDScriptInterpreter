INCS = cmdline.h expr.h parse.h val.h pointer.h env.h step.h cont.h

INCSTEST = exec.h

SRCS = main.cpp cmdline.cpp test.cpp expr.cpp parse.cpp val.cpp env.cpp step.cpp cont.cpp

SRCSTEST = test_msdscript.cpp exec.cpp
msdscript: $(SRCS) $(INCS) ; c++ --std=c++14 -O2 -fsanitize=undefined -fno-sanitize-recover=undefined -o msdscript $(SRCS)
test_msdscript: $(SRCSTEST) $(INCSTEST) ; c++ --std=c++14 -O2 -o test_msdscript $(SRCSTEST)
.PHONY: test
test: msdscript
	./msdscript --test


INCS_libImage = expr.h parse.h val.h pointer.h env.h step.h cont.h

SRCS_libImage = test.cpp expr.cpp parse.cpp val.cpp env.cpp step.cpp cont.cpp

libraryImage: $(SRCS_libImage) $(INCS_libImage) ; gcc --std=c++14  -c test.cpp expr.cpp parse.cpp val.cpp env.cpp step.cpp cont.cpp
	$(SRCS) $(INCS) ; ar -ruv libraryImage.a test.o expr.o parse.o val.o env.o step.o cont.o



