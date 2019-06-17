.SUFFIXES:
.SECONDARY:

TARGET  := Transform-Feedback
BUILD   := build
SOURCES := src

######################################################################################
CXXFLAGS += -Wall -Wextra -O2 -ggdb3

LDFLAGS += -lglut -lGLEW -lGL -pthread

ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------
export OUTPUT   :=      $(CURDIR)/$(BUILD)/$(TARGET)
export VPATH    :=      $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR  :=      $(CURDIR)/$(BUILD)
CXXFILES        :=      $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cc)))

export LD       :=      $(CXX)
export OFILES   :=      $(CXXFILES:.cc=.o)

export OUTPUT   :=      $(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(OUTPUT)
#---------------------------------------------------------------------------------
else

# main targets
$(OUTPUT): $(OFILES)
	@echo '[1m[[35mLD[37m][0m' $(notdir $@)
	@$(LD) $^ -o $@ $(LIBPATHS) $(LDFLAGS)

-include $(DEPSDIR)/*.d
endif
##################################################################################
%.o: %.cc
	@echo '[1m[[32mCC[37m][0m' $(notdir $<)
	@$(CXX) -MMD -MP -MF $(DEPSDIR)/$*.d $(CXXFLAGS) $(CPPFLAGS) $(INCLUDE) -c $< -o $@

