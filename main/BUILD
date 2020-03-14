load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "utils", 
    srcs = ["utils.cc"], 
    hdrs = ["utils.h"], 
)

cc_library(
    name = "parser", 
    srcs = ["parser.h"],
)

cc_library(
    name = "logging_v2", 
    srcs = ["logging_v2.h"],
    visibility = ["//test:__pkg__"],
)

cc_library(
    name = "logging", 
    srcs = ["logging.cc"],
    hdrs = ["logging.h"],
    deps = [":utils"], 
    visibility = ["//test:__pkg__"],
)

cc_library(
    name = "row", 
    srcs = ["row.cc"], 
    hdrs = ["row.h"], 
)

cc_library(
    name = "table", 
    srcs = ["table.cc"], 
    hdrs = ["table.h", "state.h"], 
    deps = [
        ":row", 
        ":logging" 
    ]
)

cc_library(
    name = "statement", 
    srcs = ["statement.cc"],
    hdrs = ["statement.h"],
    deps = [
        ":utils", 
        ":parser", 
        ":row", 
        ":table"
    ], 
    visibility = ["//test:__pkg__"],
)

cc_binary(
    name = "casualdb", 
    srcs = ["casualdb.cc"], 
    deps = [
        "statement"
    ],
    visibility = ["//test:__pkg__"],
)
