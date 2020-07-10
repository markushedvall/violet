from conans import ConanFile, CMake, tools

class VioletConan(ConanFile):
    name = "violet"
    version = "0.1.0"
    license = "MIT"
    author = "Markus Hedvall mackanhedvall@gmail.com"
    url = "https://github.com/markushedvall/violet"
    description = "C++ cross-platform applications and graphics library"
    topics = ("cross-platform", "application", "graphics", "renderer")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake_find_package_multi"
    exports_sources = "CMakeLists.txt", "LICENSE", "src/*", "include/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build_requirements(self):
        if not self.in_local_cache:
            self.build_requires("catch2/2.12.2")

    def imports(self):
        if not self.in_local_cache:
            self.copy("*/Catch.cmake", keep_path =False)
            self.copy("*/CatchAddTests.cmake", keep_path =False)

    def build(self):
        cmake = CMake(self)
        cmake.definitions["VIOLET_TEST"] = False
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("LICENSE", dst="licenses")
        self.copy("*.h", dst="include", src="include")
        self.copy("*violet.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["violet"]
