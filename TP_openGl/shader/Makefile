TARGET  := shader
BUILD   := build
SOURCES := src src/math
######################################################################################
.SUFFIXES:
.SECONDARY:
CXXFLAGS += -Wall -Wextra -O2 -ggdb3 -I../src/math -std=c++11
LDFLAGS += -L/usr/lib/nvidia-384 -lglut -lGLEW -lGL -pthread 
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
%.o: %.cc
	@echo '[1m[[32mCC[37m][0m' $(notdir $<)
	@$(CXX) -MMD -MP -MF $(DEPSDIR)/$*.d $(CXXFLAGS) $(CPPFLAGS) $(INCLUDE) -c $< -o $@
