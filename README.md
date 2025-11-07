# 🎛️ Lightbender VST3 Plugin

**Lightbender** is an experimental audio effect built with **JUCE** and **CMake**, designed to explore real-time FFT-based sound manipulation.

---

## 🔍 Overview

Lightbender takes incoming audio, splits it into frequency components using a **Fast Fourier Transform (FFT)**, and reconstructs it back in real-time after applying various spectral transformations.

The current focus is on:
- safe and stable **FFT → IFFT passthrough**
- **spectral flipping** (horizontal/vertical)
- clean normalization and limiter protection

Future goals include:
- dynamic spectral morphing
- noise shaping and harmonic rebalancing
- visual FFT display using the JUCE GUI system

---

## 🧠 Core Features

- **Real-Time FFT Processing** — 2048-sample Hann-windowed FFT for smooth spectral control.  
- **Spectral Manipulation** — frequency and amplitude domain operations (mirror, invert, etc).  
- **Limiter Safety Layer** — prevents output spikes during experimental processing.  
- **Modular DSP Chain** — easily extendable for future effects and visualizers.  

---

## ⚙️ Tech Stack

| Component | Purpose |
|------------|----------|
| **JUCE 8** | Audio framework for plugin architecture (VST3). |
| **CMake** | Cross-platform build and configuration. |
| **Visual Studio 2022 (MSVC)** | Primary build tool on Windows. |
| **VST3 SDK** | Audio plugin format target. |

---

## 🏗️ Build Instructions (Windows)

```powershell
# Clone repository
git clone https://github.com/etherOnGitHub/vst3One.git
cd vst3One

# Initialize JUCE submodule
git submodule update --init --recursive

# Generate project files for Visual Studio 2022 (x64)
cmake -S . -B build -G "Visual Studio 17 2022" -A x64

# Build release version
cmake --build build --config Release
```

After building, the plugin file will be located in:

```
build/Lightbender_artefacts/Release/VST3/Lightbender.vst3
```

You can manually copy it to your system’s VST3 folder if automatic install fails:
```
C:\Program Files\Common Files\VST3\
```

---

## 🧩 Roadmap

- [ ] Add GUI visualizer (spectrogram + waveform)
- [ ] Expand FFT controls (size, window type)
- [ ] Implement spectral filters & convolution
- [ ] Create parameter automation support
- [ ] WebAudio or WASM prototype for browser preview

---

## ⚠️ Notes

This plugin is currently experimental — some operations (like FFT flipping) can introduce latency or aliasing.  
Output is limiter-protected, but always test with low volume first.

---

## 🧑‍💻 Author

**etherchild** — Full Stack Developer / Audio Designer  

---

## 🪐 License

MIT License — free for modification, learning, and extension.
