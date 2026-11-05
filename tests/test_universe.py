import pexpect
import pytest

DEMO = "/work/universe"


@pytest.fixture
def demo():
    child = pexpect.spawn(DEMO, encoding="utf-8", timeout=5)
    while True:
        line = child.readline().strip()
        if line == "quit":
            break
    yield child
    child.close(force=True)


def run(demo, line):
    demo.sendline(line)
    demo.readline()              # эхо команды
    return demo.readline().strip()


# ---------- create ----------

def test_create_ok(demo):
    assert run(demo, "create alpha") == "ok"


def test_create_duplicate(demo):
    run(demo, "create alpha")
    assert run(demo, "create alpha") == "exists"


def test_create_many(demo):
    for name in ("a", "b", "c"):
        assert run(demo, f"create {name}") == "ok"
    assert run(demo, "count") == "3"


# ---------- remove ----------

def test_remove_ok(demo):
    run(demo, "create alpha")
    assert run(demo, "remove alpha") == "ok"


def test_remove_missing(demo):
    assert run(demo, "remove nope") == "not_found"


def test_remove_twice(demo):
    run(demo, "create alpha")
    run(demo, "remove alpha")
    assert run(demo, "remove alpha") == "not_found"


# ---------- rename ----------

def test_rename_ok(demo):
    run(demo, "create alpha")
    assert run(demo, "rename alpha beta") == "ok"


def test_rename_missing(demo):
    assert run(demo, "rename nope beta") == "failed"


def test_rename_to_existing(demo):
    run(demo, "create alpha")
    run(demo, "create beta")
    assert run(demo, "rename alpha beta") == "failed"


def test_rename_same_name(demo):
    run(demo, "create alpha")
    assert run(demo, "rename alpha alpha") == "failed"


# ---------- change / current ----------

def test_current_none(demo):
    assert run(demo, "current") == "none"


def test_change_ok(demo):
    run(demo, "create alpha")
    assert run(demo, "change alpha") == "ok"


def test_change_missing(demo):
    assert run(demo, "change nope") == "not_found"


def test_current_after_change(demo):
    run(demo, "create alpha")
    run(demo, "change alpha")
    assert run(demo, "current") == "alpha"


def test_remove_current_clears(demo):
    run(demo, "create alpha")
    run(demo, "change alpha")
    run(demo, "remove alpha")
    assert run(demo, "current") == "none"


# ---------- count / list ----------

def test_count_empty(demo):
    assert run(demo, "count") == "0"


def test_list_empty(demo):
    assert run(demo, "list") == "."


def test_list_contains_all(demo):
    for name in ("alpha", "beta", "gamma"):
        run(demo, f"create {name}")
    demo.sendline("list")
    demo.readline()  # эхо "list"
    names = set()
    while True:
        line = demo.readline().strip()
        if line == ".":
            break
        names.add(line)
    assert names == {"alpha", "beta", "gamma"}