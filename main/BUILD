load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "deck",
    hdrs = ["deck.h"],
)

cc_library(
    name = "hand",
    hdrs = ["hand.h"],
)

cc_binary(
    name = "blackjack",
    srcs = ["blackjack.cc"],
    deps = [":deck", ":hand"],
)

