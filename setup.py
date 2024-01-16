from setuptools import Extension, setup


def main():
    setup(name='FastAlgos',
          version='0.1.0',
          description='Fast algos & structures for Python from C',
          ext_modules=[Extension('FastAlgos', ['karatsuba.c', 'knuth_morris_pratt.c', 'fast_algos.c',
                                               'doubly_linked_list.c', "doubly_linked_list_methods.c"])])


if __name__ == '__main__':
    main()