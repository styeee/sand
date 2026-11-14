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