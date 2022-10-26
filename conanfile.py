from conans import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps


class EIPScannerConan(ConanFile):
    name = "EIPScanner"
    version = "0.1.3"
    settings = "os", "arch", "compiler", "build_type"
    generators = "cmake_find_package"

    def export_sources(self):
        self.copy("*")

    def generate(self):
        CMakeToolchain(self).generate()
        CMakeDeps(self).generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.libdirs = ["lib"]
        self.cpp_info.libs = ["EIPScanner"]
