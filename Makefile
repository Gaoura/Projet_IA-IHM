# Modes : normal, perfect (pour etre plus tatillon), debug (pour gdb), release (optimisee)
MODE				?= normal

#////////////////////////////////////////////////////////////////////////////////////////////
#
#              ######   #######  ##     ## ########  #### ##        #######
#             ##    ## ##     ## ###   ### ##     ##  ##  ##       ##     ##
#             ##       ##     ## #### #### ##     ##  ##  ##       ##     ##
#             ##       ##     ## ## ### ## ########   ##  ##       ##     ##
#             ##       ##     ## ##     ## ##         ##  ##       ##     ##
#             ##    ## ##     ## ##     ## ##         ##  ##       ##     ##
#              ######   #######  ##     ## ##        #### ########  #######
#
#////////////////////////////////////////////////////////////////////////////////////////////

CXX				:= g++

# flags minimum necessaires
CXXFLAGS 		:= -Wall -Wextra -std=c++11 -pedantic
LDFLAGS			:=
FLAGS				:= $(CXXFLAGS)

# changer tous les warnings en erreur et s'arreter a la premiere erreur
PERFECT_FLAGS	:= -Werror -Wfatal-errors
# options de debug
DEBUG_FLAGS		:= -g
# optimisations
OPTI_FLAGS		:= -O2

# Chargement des flags en fonction du mode choisi
ifeq ($(MODE),perfect)
	FLAGS += $(PERFECT_FLAGS)
else
ifeq ($(MODE),debug)
	FLAGS += $(DEBUG_FLAGS)
else
ifeq ($(MODE),release)
	FLAGS += $(OPTI_FLAGS)
endif
endif
endif

#////////////////////////////////////////////////////////////////////////////////////////////
#
#                       ########  ########  ######  ######## ########
#                       ##     ## ##       ##    ##    ##    ##
#                       ##     ## ##       ##          ##    ##
#                       ########  ######    ######     ##    ######
#                       ##   ##   ##             ##    ##    ##
#                       ##    ##  ##       ##    ##    ##    ##
#                       ##     ## ########  ######     ##    ########
#
#////////////////////////////////////////////////////////////////////////////////////////////

VPATH				:= src

# repertoire des executables
TESTS_DIR		:= bin
# repertoire des .o
OBJS_DIR			:= objs

DIR				:= $(TESTS_DIR) $(OBJS_DIR)

# tous les fichiers .cpp sauf les fichiers de tests
SRC				:= $(notdir $(filter-out $(wildcard $(VPATH)/Test*), $(wildcard $(VPATH)/*.cpp)))
OBJS				:= $(SRC:.cpp=.o)

# les sources ecrites
#SRC				:= InfoSommetCarte.o InfoAreteCarte.o GElement.o
# les sources fournies
#LIB				:= DessinGrapheRecuitSimule.o DessinGraphe.o OutilsCarteRecuitSimule.o Vecteur2D.o

#OBJS				:= $(SRC) $(LIB)

# executables de tests
EXEC 				:= TestPElement.out TestGraphe.out TestGraphePourRecuitSimule.out

#////////////////////////////////////////////////////////////////////////////////////////////
#
#                 ########  ########  ######   ##       ########  ######
#                 ##     ## ##       ##    ##  ##       ##       ##    ##
#                 ##     ## ##       ##        ##       ##       ##
#                 ########  ######   ##   #### ##       ######    ######
#                 ##   ##   ##       ##    ##  ##       ##             ##
#                 ##    ##  ##       ##    ##  ##       ##       ##    ##
#                 ##     ## ########  ######   ######## ########  ######
#
#////////////////////////////////////////////////////////////////////////////////////////////

.PHONY: all clean cleanall $(DIR)

all: $(DIR) $(addprefix $(TESTS_DIR)/, $(EXEC))

# Construction des repertoires recevant les .o et executables
$(DIR):
	@mkdir -p $@

# Construction des .o
$(OBJS_DIR)/%.o: %.cpp
	@$(CXX) -c $(FLAGS) $< -o $@

# Construction de TestPElement
$(TESTS_DIR)/TestPElement.out: $(addprefix $(OBJS_DIR)/,TestPElement.o)
	@$(CXX) $^ $(LDFLAGS) -o $@

# Construction de TestGraphe
$(TESTS_DIR)/TestGraphe.out: $(addprefix $(OBJS_DIR)/,GElement.o TestGraphe.o)
	@$(CXX) $^ $(LDFLAGS) -o $@

# Construction de TestGraphePourRecuitSimule
$(TESTS_DIR)/TestGraphePourRecuitSimule.out: $(addprefix $(OBJS_DIR)/,$(OBJS) TestGraphePourRecuitSimule.o)
	@$(CXX) $^ $(LDFLAGS) -o $@

# Regles pour raccourcir l'appel a un mode (evitant de devoir passer une variable a make)
perfect:
	@$(MAKE) --no-print-directory MODE=perfect
debug:
	@$(MAKE) --no-print-directory MODE=debug
release:
	@$(MAKE) --no-print-directory MODE=release


# Suppression des .o et du repertoire les recevant
clean:
	@rm -f $(OBJS_DIR)/*.o
	@rmdir $(OBJS_DIR)

# Suppression des executables et du repertoire les recevant + clean
cleanall: clean
	@rm -f $(TESTS_DIR)/*.out
	@rmdir $(TESTS_DIR)
