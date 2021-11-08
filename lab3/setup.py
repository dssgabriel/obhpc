from distutils.core import setup, Extension

mblas_module = Extension("mblas", sources = [ "mblas_core.c", "mblas.c" ])
setup(
    name = "mblas",
    version = "0.1",
    description = "My single precision BLAS library",
    ext_modules = [ mblas_module ]
)
