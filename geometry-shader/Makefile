# Partie configurable
TARGET  := debug-normal
BUILD   := build
SOURCES := src lib
INCLUDE := lib

CXXFLAGS += -Wall -Wextra -O2 -ggdb3 -std=c++11
LDFLAGS  += -lglut -lGLEW -lGL -pthread
######################################################################################
CPPFLAGS += $(foreach dir,$(INCLUDE),-I../$(dir))
.SUFFIXES:
.SECONDARY:
# ------------------------------------------------------------------------------------
%.o: %.cc
	@echo '[1m[[32mCC[37m][0m' $(notdir $<)
	@$(CXX) -MMD -MP -MF $(DEPSDIR)/$*.d $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
# ------------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
export OUTPUT   :=      $(CURDIR)/$(BUILD)/$(TARGET)
export VPATH    :=      $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR  :=      $(CURDIR)/$(BUILD)
CXXFILES        :=      $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cc)))
export OFILES   :=      $(CXXFILES:.cc=.o)
export LD       :=      $(CXX)
export OUTPUT   :=      $(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	@echo clean ...
	@rm -fr $(BUILD) $(OUTPUT)
else
$(OUTPUT): $(OFILES)
	@echo '[1m[[35mLD[37m][0m' $(notdir $@)
	@$(LD) $^ -o $@ $(LIBPATHS) $(LDFLAGS)
-include $(DEPSDIR)/*.d
endif
