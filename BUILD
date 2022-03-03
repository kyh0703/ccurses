cc_library (
    name = "ccurses",
    hdrs = glob(["include/*.h"]),
    srcs = glob(["src/*.cpp"]),
    copts = [
        "-std=c++11",
        "-Iinclude",
        "-g",
        "-O0",
        "-fPIC",
        "-Wall",
    ],
)
cc_test (
    name = "ccurses_test",
    srcs = ["example/Test.cpp"],
    deps = [
        "ccurses"
    ],
    copts = [
        "-std=c++11",
        "-Iinclude",
    ],
    linkopts = ["-lncursesw"]
)