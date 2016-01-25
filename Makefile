default: release

.PHONY: default release debug all clean

include make-utils/flags.mk
include make-utils/cpp-utils.mk

CXX_FLAGS += -pthread -pedantic
LD_FLAGS += -lmongoose

$(eval $(call auto_folder_compile,src))
$(eval $(call auto_add_executable,test))

release: release_test
release_debug: release_debug_test
debug: debug_test

all: release release_debug debug

run: release
	./release/bin/test

clean: base_clean

include make-utils/cpp-utils-finalize.mk
