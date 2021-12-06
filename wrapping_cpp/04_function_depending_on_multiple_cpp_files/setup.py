from Cython.Build import cythonize
from Cython.Distutils import build_ext
from setuptools import setup
from setuptools.extension import Extension


extensions = [
    Extension(
        "test_module.calculator",
        [
            "test_module/calculator_wrapper.pyx",
            "test_module/calculator.cpp",
            "test_module/result.cpp",
            "test_module/addition.cpp",
            "test_module/subtraction.cpp"
        ],
        language="c++",
    )
]

setup(cmdclass={"build_ext": build_ext}, ext_modules=cythonize(extensions))
