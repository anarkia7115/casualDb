load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
cc_library(
    name = "utils", 
    srcs = ["utils.h"],
)

cc_library(
    name = "logging_v2", 
    srcs = ["logging_v2.h"],
    deps = ["utils"], 
    visibility = ["//test:__pkg__"],
)

cc_library(
    name = "logging", 
    srcs = ["logging.cc"],
    hdrs = ["logging.h"],
    deps = ["utils"], 
    visibility = ["//test:__pkg__"],
)

cc_library(
    name = "row", 
    srcs = ["row.cc"], 
    hdrs = ["row.h", "state.h"]
)

cc_library(
    name = "table", 
    srcs = ["table.cc"], 
    hdrs = ["table.h", "state.h"], 
    deps = [":row"]
)

cc_library(
    name = "statement", 
    srcs = ["statement.cc", "row.cc"],
    hdrs = ["statement.h", "parser.h"],
    deps = [":utils", ":table", ":row"],
    visibility = ["//test:__pkg__"],
)

cc_library(
    name = "repl", 
    srcs = ["repl.cc"], 
    hdrs = ["repl.h"], 
    deps = [
        ":statement",
        ":utils", 
    ],
    visibility = ["//test:__pkg__"],
)

cc_binary(
    name = "casualdb", 
    deps = [
        ":repl",
    ]
)