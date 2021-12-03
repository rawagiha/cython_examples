from Cython.Build import cythonize
from Cython.Distutils import build_ext
from setuptools import setup
from setuptools.extension import Extension


extensions = [
    Extension(
        "make_my_car", ["make_my_car_wrapper.pyx", "make_my_car.cpp"], language="c++"
    )
]

setup(cmdclass={"build_ext": build_ext}, ext_modules=cythonize(extensions))
