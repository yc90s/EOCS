BIN := VM

ifeq (${BUILD_TYPE}, release)
	CXXFLAGS += -Wall -O2 -finline-limit=1000 -fdiagnostics-color=auto -std=c++11 -DNDEBUG
	CFLAGS += -Wall -O2 -finline-limit=1000 -fdiagnostics-color=auto -std=c++11 -DNDEBUG
else
	CXXFLAGS += -Wall -g -O0 -fdiagnostics-color=auto -std=c++11
	CFLAGS += -Wall -g -O0 -fdiagnostics-color=auto -std=c++11
endif

CPP_FILES += $(wildcard *.cpp)
CC_FILES += $(wildcard *.cc)
C_FILES += $(wildcard *.c)
H_FILES += $(wildcard *.h)

INC +=
LIBS +=

BIN_PATH = .
OBJ_DIR = ./obj
$(shell if [ ! -d ${OBJ_DIR} ]; then mkdir ${OBJ_DIR}; fi;)

OBJS := $(patsubst %.cpp, ${OBJ_DIR}/%.o, ${CPP_FILES}) $(patsubst %.cc, ${OBJ_DIR}/%.o, ${CC_FILES}) $(patsubst %.c, ${OBJ_DIR}/%.o, ${C_FILES})
TARGET := ${BIN_PATH}/${BIN}

.PHONY: all clean

all: ${TARGET}
	@echo Target... ${BIN}

${TARGET}:${OBJS} ${H_FILES}
	@echo link.. $@
	${CXX} ${CXXFLAGS} -o $@ ${OBJS} ${INC} ${LIBS}

${OBJ_DIR}/%.o:%.c
	${CC} ${CFLAGS} -c -o $@ $< ${INC}

${OBJ_DIR}/%.o:%.cc
	${CXX} ${CXXFLAGS} -c -o $@ $< ${INC}

${OBJ_DIR}/%.o:%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $< ${INC}

clean:
	rm -f ${TARGET} ${OBJS}
