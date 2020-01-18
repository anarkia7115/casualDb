load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
cc_library(
    name = "utils", 
    srcs = ["utils.h"],
)

cc_library(
    name = "statement", 
    srcs = ["statement.cc", "parser.h"],
    hdrs = ["statement.h"],
    deps = [":utils"],
)

cc_library(
    name = "repl", 
    srcs = ["repl.cc"], 
    hdrs = ["repl.h"], 
    deps = [
        ":statement",
        ":utils", 
    ],
)

cc_binary(
    name = "casualdb", 
    deps = [
        ":repl",
    ]
)