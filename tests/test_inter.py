import pytest
import pexpect

DEMO="/work/inter"

@pytest.fixture
def demo():
	child=pexpect.spawn(DEMO)
	yield child
	child.close()

def test_print(demo):
	demo.sendline("print(1+1)")
	demo.readline()
	a=demo.readline()
	assert a.strip()==b"2"

import pytest
import pexpect

DEMO = "/work/inter"


@pytest.fixture
def demo():
	child = pexpect.spawn(DEMO)
	yield child
	child.close()


def test_print(demo):
	demo.sendline("print(1+1)")
	demo.readline()
	a = demo.readline()
	assert a.strip() == b"2"


def test_syntax_error(demo):
	demo.sendline("gffd654*()YHN")
	demo.readline()
	a = demo.readline()
	assert b"expected" in a


def test_runtime_error(demo):
	demo.sendline("p()")
	demo.readline()
	a = demo.readline()
	assert b"nil value" in a