# ==============================================================================
# COMPILER AND FLAG SETTINGS
# ==============================================================================
CC       := gcc

# FLAGS
CFLAGS   := -std=c23 -Wall -Wextra -O3
CFLAGS   += -I./include

LDFLAGS  := -L./lib
LDFLAGS  += -lraylib -lGL -lm -lpthread -ldl -lrt -lX11


# ==============================================================================
# FOLDERS AND AUTOMATIC FILE SEARCHING
# ==============================================================================
TARGET   := game.app

# Búsqueda recursiva
SRCS     := main.c $(wildcard systems/logic/*.c) $(wildcard systems/render/*.c) $(wildcard loaders/*.c) $(wildcard spawners/*.c)

# Conversión de archivos .c a archivos de objeto .o
OBJ_DIR  := build
OBJS     := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# ==============================================================================
# COMPILER RULES
# ==============================================================================

# Default
all: $(TARGET)

# Executable link
$(TARGET): $(OBJS)
	@echo "=> Enlazando el ejecutable final: $(TARGET)"
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Source code to .o (Regla genérica para archivos .c)
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "-> Compilando: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	@echo "=> Limpiando archivos temporales..."
	rm -rf $(OBJ_DIR) $(TARGET)

run:
	@echo "=> Ejecutando juego..."
	mangohud ./$(TARGET)

# Avoid conflicts
.PHONY: all clean run
