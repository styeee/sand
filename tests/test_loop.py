import pexpect
import pytest

DEMO = "/work/loop"


@pytest.fixture
def demo():
    child = pexpect.spawn(DEMO, ["5", "0.001"], encoding="utf-8", timeout=1)
    yield child
    child.close(force=True)


def test_squares(demo):
    for t in range(1, 5):
        demo.sendline("3")
        demo.expect_exact(f"{t}:9\r\n")


def test_negative_input(demo):
    demo.sendline("-3")
    demo.expect_exact("1:9\r\n")


def test_zero_input(demo):
    demo.sendline("0")
    demo.expect_exact("1:0\r\n")


def test_stops_at_5(demo):
    for _ in range(4):
        demo.sendline("2")
        demo.expect_exact(":4\r\n")
    demo.sendline("2")
    demo.expect_exact("5:4\r\n")
    demo.expect(pexpect.EOF)