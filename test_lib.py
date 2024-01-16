import pytest

from FastAlgos import DLL, karatsuba, knuth_morris_pratt

def test_dll_init():
    dll = DLL([1, 2, 3])

    assert isinstance(dll, DLL)
    assert dll.head == 1
    assert dll.tail == 3


def test_dll_init_raises():
    with pytest.raises(TypeError):
        dll = DLL([1, '2'])

    a = b'awd'
    with pytest.raises(TypeError):
        dll = DLL([1, a])


def test_dll_append():
    dll = DLL([1, 2])

    dll.append(3)
    assert dll.tail == 3
    dll.append(-1)
    assert dll.tail == -1


def test_dll_append_raises():
    dll = DLL([1, 2])
    with pytest.raises(TypeError):
        dll.append('2')
    
    with pytest.raises(TypeError):
        dll.append(TypeError)


def test_dll_append_left():
    dll = DLL([1, 2])

    dll.append_left(3)
    assert dll.head == 3
    dll.append_left(-1)
    assert dll.head == -1


def test_dll_append_left_raises():
    dll = DLL([1, 2])
    with pytest.raises(TypeError):
        dll.append_left('2')
    
    with pytest.raises(TypeError):
        dll.append_left(TypeError)


def test_dll_insert():
    dll = DLL([1, 2])

    dll.insert(2, 3)
    assert dll.tail == 3
    dll.insert(1, 4)
    dll.delete(1)
    assert dll.head == 4


def test_dll_insert_raises():
    dll = DLL([1, 2])
    with pytest.raises(TypeError):
        dll.insert('2', 3)
    
    with pytest.raises(TypeError):
        dll.insert(2, '2')

    with pytest.raises(IndexError):
        dll.insert(10, 10)


def test_dll_pop_tail():
    dll = DLL([1, 2])

    assert dll.pop_tail() == 2
    assert dll.pop_tail() == 1

    with pytest.raises(IndexError):
        dll.pop_tail()


def test_dll_pop_head():
    dll = DLL([1, 2])

    assert dll.pop_head() == 1
    assert dll.pop_head() == 2

    with pytest.raises(IndexError):
        dll.pop_head()


def test_dll_delete():
    dll = DLL([1, 2, 3, 4, 5])

    dll.delete(5)
    assert dll.tail == 4

    dll.delete(1)
    assert dll.head == 2

    dll.delete(3)
    assert dll.head == 2
    assert dll.tail == 4

    dll.delete(4)
    assert dll.head == dll.tail == 2


def test_dll_is_iterable():
    dll = DLL([1, 2, 3, 4, 5])

    for i, val in enumerate(dll, 1):
        assert i == val

        
def test_karatsuba():
    first = 1565120651
    second = 1565130951

    expected = first * second
    assert karatsuba(first, second) == expected


def test_karatsuba_raises():
    first = 1565120651
    second = 'a'

    with pytest.raises(TypeError):
        karatsuba(first, second)


def test_knuth_morris_pratt():
    text = "asrnaocvepromgoismweroingxkzmfepojgeposdlfv"
    pattern = "weroing"

    expected = text.index(pattern)
    assert expected == knuth_morris_pratt(text, pattern)


def test_knuth_morris_pratt_raises():
    text = "asrnaocvepromgoismweroingxkzmfepojgeposdlfv"
    pattern = "aaaaaaaaaaaaa"

    with pytest.raises(ValueError):
        knuth_morris_pratt(text, pattern)

    pattern = 12

    with pytest.raises(TypeError):
        knuth_morris_pratt(text, pattern)