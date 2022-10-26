from conans import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps


class EIPScannerConan(ConanFile):
    name = "EIPScanner"
    version = "1.3.0"
    settings = "os", "arch", "compiler", "build_type"
    generators = "cmake_find_package"

    def export_sources(self):
        self.copy("src/*")
        self.copy("CMakeLists.txt")
        self.copy("LICENSE")

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
        self.copy("license*", dst="licenses", ignore_case=True)

    def package_info(self):
        self.cpp_info.includedirs = ["include", "include/EIPScanner"]
        self.cpp_info.libdirs = ["lib"]
        self.cpp_info.libs = ["EIPScanner"]
