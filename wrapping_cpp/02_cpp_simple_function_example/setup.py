from Cython.Build import cythonize
from Cython.Distutils import build_ext
from setuptools import setup
from setuptools.extension import Extension


extensions = [
    Extension(
        "concat", ["concat_string_wrapper.pyx", "concat_string.cpp"], language="c++"
    )
]

setup(cmdclass={"build_ext": build_ext}, ext_modules=cythonize(extensions))
