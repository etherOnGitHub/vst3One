cmake_minimum_required(VERSION 3.15)

project(Lightbender VERSION 0.0.1 LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- JUCE options: keep things lean and kill VST2 ---
set(JUCE_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(JUCE_BUILD_EXTRAS OFF   CACHE BOOL "" FORCE)
set(JUCE_BUILD_VST2    OFF  CACHE BOOL "" FORCE)
set(JUCE_VST2_HEADERS_PATH "" CACHE PATH "" FORCE)

set(JUCE_PLUGINHOST_VST OFF CACHE BOOL "" FORCE)
set(JUCE_PLUGINHOST_VST3 ON  CACHE BOOL "" FORCE)
set(JUCE_PLUGINHOST_AU OFF   CACHE BOOL "" FORCE)
set(JUCE_PLUGINHOST_LV2 OFF  CACHE BOOL "" FORCE)
set(JUCE_PLUGINHOST_AAX OFF  CACHE BOOL "" FORCE)

# --- Add JUCE, with its own binary dir ---
add_subdirectory(JUCE ${CMAKE_BINARY_DIR}/JUCE_build)

# --- Define the plugin target ---
juce_add_plugin(Lightbender
    PLUGIN_NAME "Lightbender"
    PRODUCT_NAME "Lightbender"
    COMPANY_NAME "aetherwaveAudio"

    VERSION ${PROJECT_VERSION}

    FORMATS VST3               # keep it simple for now
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD TRUE
    IS_MIDI_EFFECT FALSE
    VST3_CAN_REPLACE_VST2 FALSE
)

target_compile_definitions(Lightbender PRIVATE
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING=1
)

# --- Generate JuceHeader.h for this target ---
juce_generate_juce_header(Lightbender)

# --- Your source files ---
target_sources(Lightbender PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
)

# --- JUCE modules you actually use ---
target_link_libraries(Lightbender PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
)
