BASH := bash
EC := ../EdgeConnectivity/EdgeConnectivity

TEST_INPUTS := $(wildcard *.in)
TESTS := $(TEST_INPUTS:.in=.test)

test: $(TESTS)

%.test: %.in %.out
	$(BASH) -c 'diff -u $(word 2,$^) <($(EC) $<)'
