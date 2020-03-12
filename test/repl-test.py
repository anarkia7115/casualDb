import textwrap
import pytest
import subprocess


def exec_sql(input_sql: list):
    p = subprocess.Popen("./casualdb", 
        stdin=subprocess.PIPE, 
        stdout=subprocess.PIPE)

    output = p.communicate("\n".join(input_sql).encode())
    return output[0].strip().split(b"\n")


def test_repl_insert_full():
    do_sql = ["insert {i} www.{i}.com News[{i}]".format(i=i) for i in range(1000)]
    do_sql.append(".exit")
    output = exec_sql(do_sql)

    assert output[-3] == b"db > Error: Table full."
    

def test_repl_insert_one():
    sql = [
        "insert 1 www.1.com News[1]", 
        "select", 
        ".exit"
    ]
    output = exec_sql(sql)
    expected_output = [
        "db > Executed!", 
        "db > (1, www.1.com, News[1])", 
        "Executed!", 
        "db > Bye!", 
    ]
    assert output == [row.encode() for row in expected_output]


def test_big_row():
    url = "w"*255
    title = "n"*255
    script = [
        "insert 1 {} {}".format(url, title), 
        "select", 
        ".exit"
    ]
    output = exec_sql(script)
    expected_output = [
        "db > Executed!", 
        "db > (1, {}, {})".format(url, title), 
        "Executed!", 
        "db > Bye!", 
    ]
    assert output == [row.encode() for row in expected_output]


def test_too_long_row():
    url = "w"*256
    title = "n"*256
    script = [
        "insert 1 {} {}".format(url, title), 
        "select", 
        ".exit"
    ]
    output = exec_sql(script)
    expected_output = [
        "db > String is too long.", 
        "db > Executed!", 
        "db > Bye!", 
    ]
    assert output == [row.encode() for row in expected_output]


def test_too_long_row():
    script = [
        "insert -1 www.-1.com News[-1]", 
        "select", 
        ".exit"
    ]
    output = exec_sql(script)
    expected_output = [
        "db > ID must be positive.", 
        "db > Executed!", 
        "db > Bye!", 
    ]
    assert output == [row.encode() for row in expected_output]


def test_data_persistence():
    script = [
        "insert 1 www.1.com News[1]", 
        ".exit"
    ]
    output = exec_sql(script)
    assert output == [
        b"db > Executed!", 
        b"db > Bye!", 
    ]

    assert exec_sql([
        "select",
        ".exit", 
    ]) == [
        b"db > (1, www.1.com, News[1])", 
        b"db > Executed!", 
        b"db > Bye!", 
    ]
