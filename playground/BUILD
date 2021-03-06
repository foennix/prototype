cc_library(
    name = "hello_world_lib",
    hdrs = ["hello_world_lib.h"],
    srcs = ["hello_world_lib.cc"]
)

# A multiple choice dialog for use in SFML.
cc_library(
    name = "dialog_box",
    hdrs = ["dialog_box.h"],
    srcs = ["dialog_box.cc"],
    deps = [":click_handler"],
    copts = ["-I/usr/local/include/"],
)

# An abstract class to implement click handlers for use in dialog boxes
cc_library(
    name = "click_handler",
    hdrs = ["click_handler.h"],
    srcs = ["click_handler.cc"]
)

# Model classes for the solar system represented int the starfield.
cc_library(
     name = "solar_system_model",
     hdrs = ["solar_system_model.h"],
     srcs = ["solar_system_model.cc"]
)

# View classes for the solar system. These offer draw functions.
cc_library(
     name = "solar_system_view",
     hdrs = ["solar_system_view.h"],
     srcs = ["solar_system_view.cc"],
     deps = [":solar_system_model"],
     copts = ["-I/usr/local/include/"],
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
    deps = [":dialog_box", ":click_handler"],
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
    name = "sfml_zoomable_starfield",
    srcs = ["sfml_starfield.cc"],
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
     deps = [":solar_system_model",
             ":solar_system_view"],
     data = [
        ":Img/sun.png"
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
