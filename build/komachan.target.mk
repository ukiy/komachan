# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := komachan
DEFS_Debug := \
	'-DNODE_GYP_MODULE_NAME=komachan' \
	'-D_DARWIN_USE_64_BIT_INODE=1' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DBUILDING_NODE_EXTENSION' \
	'-DDEBUG' \
	'-D_DEBUG'

# Flags passed to all source files.
CFLAGS_Debug := \
	-O0 \
	-gdwarf-2 \
	-mmacosx-version-min=10.7 \
	-arch x86_64 \
	-Wall \
	-Wendif-labels \
	-W \
	-Wno-unused-parameter

# Flags passed to only C files.
CFLAGS_C_Debug := \
	-fno-strict-aliasing

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-std=gnu++0x \
	-fno-rtti \
	-fno-exceptions \
	-fno-threadsafe-statics \
	-stdlib=libc++

# Flags passed to only ObjC files.
CFLAGS_OBJC_Debug :=

# Flags passed to only ObjC++ files.
CFLAGS_OBJCC_Debug :=

INCS_Debug := \
	-I/Users/ukiy/.node-gyp/4.2.1/include/node \
	-I/Users/ukiy/.node-gyp/4.2.1/src \
	-I/Users/ukiy/.node-gyp/4.2.1/deps/uv/include \
	-I/Users/ukiy/.node-gyp/4.2.1/deps/v8/include \
	-I$(srcdir)/node_modules/nan

DEFS_Release := \
	'-DNODE_GYP_MODULE_NAME=komachan' \
	'-D_DARWIN_USE_64_BIT_INODE=1' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DBUILDING_NODE_EXTENSION'

# Flags passed to all source files.
CFLAGS_Release := \
	-Os \
	-gdwarf-2 \
	-mmacosx-version-min=10.7 \
	-arch x86_64 \
	-Wall \
	-Wendif-labels \
	-W \
	-Wno-unused-parameter

# Flags passed to only C files.
CFLAGS_C_Release := \
	-fno-strict-aliasing

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-std=gnu++0x \
	-fno-rtti \
	-fno-exceptions \
	-fno-threadsafe-statics \
	-stdlib=libc++

# Flags passed to only ObjC files.
CFLAGS_OBJC_Release :=

# Flags passed to only ObjC++ files.
CFLAGS_OBJCC_Release :=

INCS_Release := \
	-I/Users/ukiy/.node-gyp/4.2.1/include/node \
	-I/Users/ukiy/.node-gyp/4.2.1/src \
	-I/Users/ukiy/.node-gyp/4.2.1/deps/uv/include \
	-I/Users/ukiy/.node-gyp/4.2.1/deps/v8/include \
	-I$(srcdir)/node_modules/nan

OBJS := \
	$(obj).target/$(TARGET)/src/ccfiles/komachan.o \
	$(obj).target/$(TARGET)/src/ccfiles/game.o \
	$(obj).target/$(TARGET)/src/ccfiles/board.o \
	$(obj).target/$(TARGET)/src/ccfiles/search.o \
	$(obj).target/$(TARGET)/src/ccfiles/io.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))
$(OBJS): GYP_OBJCFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE)) $(CFLAGS_OBJC_$(BUILDTYPE))
$(OBJS): GYP_OBJCXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE)) $(CFLAGS_OBJCC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-undefined dynamic_lookup \
	-Wl,-search_paths_first \
	-mmacosx-version-min=10.7 \
	-arch x86_64 \
	-L$(builddir)

LIBTOOLFLAGS_Debug := \
	-undefined dynamic_lookup \
	-Wl,-search_paths_first

LDFLAGS_Release := \
	-undefined dynamic_lookup \
	-Wl,-search_paths_first \
	-mmacosx-version-min=10.7 \
	-arch x86_64 \
	-L$(builddir)

LIBTOOLFLAGS_Release := \
	-undefined dynamic_lookup \
	-Wl,-search_paths_first

LIBS :=

$(builddir)/komachan.node: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(builddir)/komachan.node: LIBS := $(LIBS)
$(builddir)/komachan.node: GYP_LIBTOOLFLAGS := $(LIBTOOLFLAGS_$(BUILDTYPE))
$(builddir)/komachan.node: TOOLSET := $(TOOLSET)
$(builddir)/komachan.node: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,solink_module)

all_deps += $(builddir)/komachan.node
# Add target alias
.PHONY: komachan
komachan: $(builddir)/komachan.node

# Short alias for building this executable.
.PHONY: komachan.node
komachan.node: $(builddir)/komachan.node

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/komachan.node

