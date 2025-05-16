CC      := cc
CFLAGS  := -std=c99 -march=native -Os -Wall -Wextra -Werror -fstack-protector-strong -fPIE -D_FORTIFY_SOURCE=2
LDFLAGS := -Wl,-O1 -Wl,-z,relro,-z,now -pie
TARGET  := wclicker
PREFIX  := /usr
BINDIR  := $(PREFIX)/bin

all: $(TARGET)

$(TARGET): wclicker.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<
	strip -s $@

install: $(TARGET)
	cp -f $(TARGET) $(BINDIR)/
	chmod 755 $(BINDIR)/$(TARGET)

uninstall:
	rm -f $(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all install uninstall clean

