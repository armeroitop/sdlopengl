
##########################################
#### MACROS
##########################################

# $(1) : Compilador
# $(2) : Objeto file a generar
# $(3) : Codigo fuente
# $(4) : Dependencias adicionales
# $(5) : Flags del compilador
define COMPILA
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef

# $(1) : Codigo fuente a cambiar a .o
define CTO
$(OBJ)/$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(1)))
endef

# $(1) : Codigo fuente a cambiar a .o
define CTH
endef

##########################################
#### CONFIG
##########################################

APP		:= imgui.a
CCFLAGS	:= -Wall
CFLAGS	:= $(CCFLAGS)
CC		:= g++
C		:= gcc
AR		:= ar
ARFLAGS	:= -crs
RANLIB	:= ranlib
MKDIR	:= mkdir -p
OBJ		:= obj
RM		:= rm

CCFLAGS += -I. -Ibackends
CFLAGS  += -I. -Ibackends

CCFLAGS += `sdl2-config --cflags`
CFLAGS += `sdl2-config --cflags`

#CPPFLAGS += $(EXTRA_INC)
#CXXFLAGS += $(EXTRA_FLAGS)

ifdef DEBUG
	CCFLAGS += -g
else
	CCFLAGS += -O3
	CFLAGS	+= -O3
endif

ALLC   := $(shell find . -type f -name '*.c')
ALLCPP := $(shell find . -type f -name '*.cpp')

# Todos los archivos .o a generar
ALLOBJ	:= $(foreach F,$(ALLC) $(ALLCPP),$(call CTO,$(F)))


# Genera la librería
$(APP): $(ALLOBJ)
	$(AR) $(ARFLAGS) $(APP) $(ALLOBJ)
	$(RANLIB) $(APP)

# Creamos las librerías de objetos
$(OBJ)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(OBJ)/%.o: %.c
	@mkdir -p $(dir $@)
	$(C) -c -o $@ $< $(CFLAGS)

#OBJSUBDIRS := $(sort $(dir $(ALLOBJ)))


#Genera la libreria
#$(APP) : $(OBJSUBDIRS) $(ALLOBJ) 
#	$(AR) $(ARFLAGS) $(APP) $(ALLOBJ)
#	$(RANLIB) $(APP) 
#
##Genera las reglas para los objetos
#$(foreach F,$(ALLCPP),$(eval $(call COMPILA,$(CC),$(call CTO,$(F)),$(F),$(call CTH,$(F)),$(CCFLAGS)))) 
#
#$(foreach F,$(ALLC),$(eval $(call COMPILA,$(C),$(call CTO,$(F)),$(F),$(call CTH,$(F)),$(CFLAGS)))) 


#$(OBJSUBDIRS) :
#	$(MKDIR) $(OBJSUBDIRS)

.PHONY: info clean cleanall

info :
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPP))
	$(info $(ALLC))
	$(info $(ALLOBJ))

clean:
	$(RM) -r ./$(OBJ)

cleanall: clean
	$(RM) -f ./$(APP)