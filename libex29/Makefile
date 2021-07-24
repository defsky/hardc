CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
#TEST_OBJ=$(patsubst %.c,%.o,$(TEST_SRC))
TEST_OBJ=$(TEST_SRC:.c=.o)

TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libex29.a

TARGET_LIB_NAME=$(patsubst build/lib%.a,%,$(TARGET))
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): $(OBJECTS)
	@mkdir -p build bin
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(OBJECTS): CFLAGS += -fPIC -c
$(OBJECTS): %.o:%.c %.h
	$(CC) $(CFLAGS) -o $@ $<

$(SO_TARGET): $(OBJECTS)
	@mkdir -p build bin
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests valgrind clean check install all build
#tests: CFLAGS += -Lbuild -l$(TARGET_LIB_NAME)
tests: $(TESTS) $(SO_TARGET)
	sh ./tests/runtests.sh

$(TESTS): %_tests:%_tests.o
	$(CC) $(CFLAGS) $(LIBS) -o $@ $<

$(TEST_OBJ): CFLAGS += -c
$(TEST_OBJ): %.o:%.c
	$(CC) $(CFLAGS) -o $@ $<
	
valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS) $(TEST_OBJ)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?car|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true


