import pytest
import pexpect

DEMO = "/work/sand"


@pytest.fixture
def demo():
	child = pexpect.spawn(DEMO)
	yield child
	child.close()


def test_current_world(demo):
	demo.sendline("print(R:current():name())")
	demo.readline()
	a = demo.readline()
	assert a.strip() == b"first"


def test_create_world(demo):
	demo.sendline("print(R:create('second'))")
	demo.readline()
	a = demo.readline()
	assert a.strip() == b"true"


def test_create_duplicate(demo):
	demo.sendline("print(R:create('first'))")
	demo.readline()
	a = demo.readline()
	assert a.strip() == b"false"


def test_count(demo):
	demo.sendline("print(R:count())")
	demo.readline()
	a = demo.readline()
	assert a.strip() == b"1"


def test_change_world(demo):
	demo.sendline("R:create('second')")
	demo.readline()
	demo.sendline("R:change('second')")
	demo.readline()
	demo.sendline("print(R:current():name())")
	demo.readline()
	a = demo.readline()
	assert a.strip() == b"second"


def test_find_world(demo):
	demo.sendline("print(R:find('first'):name())")
	demo.readline()
	a = demo.readline()
	assert a.strip() == b"first"


def test_find_missing(demo):
	demo.sendline("print(R:find('nope'))")
	demo.readline()
	a = demo.readline()
	assert a.strip() == b"nil"


def test_rename_world(demo):
	demo.sendline("R:rename('first','renamed')")
	demo.readline()
	demo.sendline("print(R:current():name())")
	demo.readline()
	a = demo.readline()
	assert a.strip() == b"renamed"


def test_world_info(demo):
	demo.sendline("R:current():info()")
	demo.readline()
	a = demo.readline()
	assert a.strip() in (b"first:day", b"first:night")