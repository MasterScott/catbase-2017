# You'd want to change this
OUT_NAME=libcatbase.so
DEBUG_BUILD=1
NO_WARNINGS=0

DEBUG_BUILD=0
NO_WARNINGS=0

LIB_DIR=lib
SRC_DIR=src
OUT_DIR=bin
TARGET=$(OUT_DIR)/$(OUT_NAME)

SSDK_DIR=source-sdk-2013-headers/mp/src
INCLUDES_SOURCESDK=-isystem$(SSDK_DIR)/public -isystem$(SSDK_DIR)/mathlib -isystem$(SSDK_DIR)/common -isystem$(SSDK_DIR)/public/tier1 -isystem$(SSDK_DIR)/public/tier0 -isystem$(SSDK_DIR)
INCLUDES=-Iinclude $(INCLUDES_SOURCESDK)
LDLIBS=
LDFLAGS=-shared -L$(realpath $(LIB_DIR)) -L/usr/lib/i386-linux-gnu
SOURCES=$(shell find $(SRC_DIR) -name "*.c*" -print)

CXX=$(shell sh -c "which g++-7 || which gcc-6 || which g++")
CC=$(shell sh -c "which gcc-7 || which gcc-6 || which gcc")
LD=$(CXX)
LDFLAGS+=-m32 -fno-gnu-unique

DEFINES+=_GLIBCXX_USE_CXX11_ABI=0 _POSIX=1 RAD_TELEMETRY_DISABLED=1 LINUX=1 USE_SDL=1 _LINUX=1 POSIX=1 GNUC=1 NO_MALLOC_OVERRIDE=1
DEFINES+=DEBUG_BUILD=$(DEBUG_BUILD)

WARNING_FLAGS=-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef
COMMON_FLAGS=-m32 -O3 -shared -Wno-unknown-pragmas -fmessage-length=0 -fvisibility=hidden -fPIC -march=native -mtune=native

ifdef DEBUG_BUILD
COMMON_FLAGS+=-g3 -ggdb
endif

CFLAGS=$(COMMON_FLAGS)
CXXFLAGS=-std=gnu++1z $(COMMON_FLAGS)

ifdef NO_WARNINGS
CFLAGS+=-w
CXXFLAGS+=-w
else
CFLAGS+=$(WARNING_FLAGS)
CXXFLAGS+=$(WARNING_FLAGS)
endif

CXXFLAGS+=$(addprefix -D,$(DEFINES))
CFLAGS+=$(addprefix -D,$(DEFINES))

CXXFLAGS+=$(INCLUDES)
CFLAGS+=$(INCLUDES)

OBJECTS=$(patsubst %.c,%.o, $(patsubst %.cpp,%.o, $(SOURCES)))
DEPENDS=$(patsubst %.c,%.d, $(patsubst %.cpp,%.d, $(SOURCES)))

.PHONY: clean echo data

all:
	mkdir -p $(OUT_DIR)
	$(MAKE) $(TARGET)
	
echo:
	echo $(OBJECTS)

# 3rd party source files, we don't need warnings there

# end of 3rd party sources

.cpp.o:
	@echo Compiling $<
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
.c.o:
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $< -o $@

%.d: %.cpp
	@$(CXX) -M $(CXXFLAGS) $< > $@

$(TARGET): $(OBJECTS)
	@echo Building...
	$(LD) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@
ifndef DEBUG_BUILD
	strip --strip-all $@
endif

clean:
	find src -type f -name '*.o' -delete
	find src -type f -name '*.d' -delete
	rm -rf ./bin

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPENDS)
endif
