from Cython.Build import cythonize
from Cython.Distutils import build_ext
from setuptools import setup
from setuptools.extension import Extension


class BuildExt(build_ext):
    def build_extensions(self):
        if '-Wstrict-prototypes' in self.compiler.compiler_so:
            self.compiler.compiler_so.remove('-Wstrict-prototypes')
        super().build_extensions()


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

setup(cmdclass={"build_ext": BuildExt}, ext_modules=cythonize(extensions))
