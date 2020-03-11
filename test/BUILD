cc_test(
    name = "parser-test",
    srcs = ["parser-test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        "//main:statement",
    ],
)

cc_test(
    name = "type-test",
    srcs = ["type-test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
    ],
)

cc_test(
    name = "logging-test",
    srcs = ["logging-test.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        "//main:logging", 
    ],
)