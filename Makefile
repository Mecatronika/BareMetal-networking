.PHONY: all clean test install
all clean test install:
	$(MAKE) -C src $@
