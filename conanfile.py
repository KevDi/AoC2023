from conan import ConanFile
from conan.tools.cmake import cmake_layout


class Aoc2023(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.test_requires("gtest/1.12.1")


    def layout(self):
        cmake_layout(self)