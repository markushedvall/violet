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
    generators = "cmake"
    exports_sources = "src/*", "include/*", "CMakeLists.txt"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*violet.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["violet"]
