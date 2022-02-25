cc_library (
    name = "ccurses",
    hdrs = glob(["include/*.h"]),
    srcs = glob(["src/*.cpp"]),
    static_library = "lcursesw",
    copts = [
        "-std=c++11",
        "-Iinclude",
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
        "-Llstdc++",
        "-Llncursesw",
    ],
)