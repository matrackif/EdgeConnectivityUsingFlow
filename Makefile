all:
	cd EdgeConnectivity && $(MAKE)

.PHONY: clean test
clean:
	cd EdgeConnectivity && $(MAKE) clean

test:
	cd test && $(MAKE) test
