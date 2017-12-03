cc_library(
    name = "hello_world_lib",
    hdrs = ["hello_world_lib.h"],
    srcs = ["hello_world_lib.cc"]
)

cc_binary(
    name = "sfml_test",
    srcs = ["sfml_test.cc"],
    copts = ["-I/usr/local/include/"],
    linkopts = [
      "-L/usr/local/lib",
      "-lsfml-graphics",
      "-lsfml-window",
      "-lsfml-system",
      "-lsfml-network",
      "-lsfml-audio",
      "-lpthread",
    ],
)

cc_binary(
    name = "sfml_user_interaction",
    srcs = ["sfml_user_interaction.cc"],
    copts = ["-I/usr/local/include/"],
    linkopts = [
      "-L/usr/local/lib",
      "-lsfml-graphics",
      "-lsfml-window",
      "-lsfml-system",
      "-lsfml-network",
      "-lsfml-audio",
      "-lpthread",
    ],
    data = [
      ":Fonts/arial.ttf"
    ],
)

cc_binary(
    name = "hello_world",
    srcs = ["hello_world.cc"],
    deps = [":hello_world_lib"],
)

cc_test(
     name = "hello_world_lib_test",
     srcs = ["hello_world_lib_test.cc"],
     deps = [":hello_world_lib",
             "@com_google_googletest//:gtest_main",]
)

# Dummy binary to make the test visible.
cc_binary(
     name = "hello_world_lib_test_dummy",
     srcs = ["hello_world_lib_test.cc"],
     deps = [":hello_world_lib",
             "@com_google_googletest//:gtest_main",]
)
