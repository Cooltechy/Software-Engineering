CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRCDIR = src
OBJDIR = obj
BINDIR = bin
FILEUTILS_DIR = ../fileHandling

SOURCES = $(wildcard $(SRCDIR)/*.c) $(FILEUTILS_DIR)/fileUtils.c
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS := $(OBJECTS:$(FILEUTILS_DIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/electricity_bill

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CC) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(FILEUTILS_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: $(TARGET)
	./$(TARGET)
