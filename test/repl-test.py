import textwrap
import pytest
import subprocess

def test_repl_insert_full():
    p = subprocess.Popen("./casualdb", 
        stdin=subprocess.PIPE, 
        stdout=subprocess.PIPE)
    do_sql = ["insert {i} www.{i}.com News[{i}]".format(i=i) for i in range(1000)]
    batch_sql = "\n".join(do_sql) + "\n.exit"
    output = p.communicate(batch_sql.encode())
    assert output[0].split(b"\n")[-3] == b"db > Error: Table full."
    

def test_repl_insert_one():
    p = subprocess.Popen("./casualdb", 
        stdin=subprocess.PIPE, 
        stdout=subprocess.PIPE)
    sql = b"insert 1 www.1.com News[1]\nselect\n.exit"
    output = p.communicate(sql)
    assert output[0].strip().split(b"\n") == [
        b"db > Executed!", 
        b"db > (1, www.1.com, News[1])", 
        b"Executed!", 
        b"db > Bye!", 
    ]