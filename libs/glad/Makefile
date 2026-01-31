
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
$(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(1)))
endef
#$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))

# $(1) : Codigo fuente a cambiar a .o
define CTH
endef
#$(patsubst %.c,%.hpp,$(patsubst %.cpp,%.hpp,$(1)))

##########################################
#### CONFIG
##########################################

APP		:= libglad.a
CCFLAGS	:= -Wall
CFLAGS	:= $(CCFLAGS)
CC		:= g++
C		:= gcc
AR		:= ar
ARFLAGS	:= -crs
RANLIB	:= ranlib
MKDIR	:= mkdir -p
SRC		:= src
OBJ		:= obj
RM		:= rm

ifdef DEBUG
	CCFLAGS += -g
else
	CCFLAGS += -O3
	CFLAGS	+= -O3
endif

SUBDIRS		:= $(shell find $(SRC) -type d)
OBJSUBDIRS	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))

ALLC		:= $(shell find src/ -type f -iname *.c)
ALLCPP		:= $(shell find src/ -type f -iname *.cpp)

# Agregamos el path de include de GLAD a los flags de compilación
CFLAGS  += -Iinclude
CCFLAGS += -Iinclude

ALLOBJ		:= $(foreach F,$(ALLC) $(ALLCPP),$(call CTO,$(F)))

.PHONY: info clean cleanall


#Genera la libreria
$(APP) : $(OBJSUBDIRS) $(ALLOBJ) 
	$(AR) $(ARFLAGS) $(APP) $(ALLOBJ)
	$(RANLIB) $(APP) 

#Genera las reglas para los objetos
$(foreach F,$(ALLCPP),$(eval $(call COMPILA,$(CC),$(call CTO,$(F)),$(F),$(call CTH,$(F)),$(CCFLAGS)))) 

$(foreach F,$(ALLC),$(eval $(call COMPILA,$(C),$(call CTO,$(F)),$(F),$(call CTH,$(F)),$(CFLAGS)))) 


$(OBJSUBDIRS) :
	$(MKDIR) $(OBJSUBDIRS)

info :
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPP))
	$(info $(ALLC))
	$(info $(ALLOBJ))

clean:
	$(RM) -r ./$(OBJ)

cleanall: clean
	$(RM) -f ./$(APP)