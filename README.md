#  🦊 Fox-Fighters(A Bullet Hell Game)
A fast-paced, retro-style SHMUP (shoot 'em up) built with [Raylib](https://www.raylib.com/), [Dear ImGui](https://github.com/ocornut/imgui) and C++,  — featuring sprite-based action, and pixel-perfect visuals

---

## 🚀 Features

- Modular C++ architecture for scalable gameplay systems
- Retro, premade fonts, pixel art, and sound effects
- Powered by Raylib + CMake for portability and performance

---

## 🕹️ Gameplay Preview

Fly as an ace fox pilot, dodge incoming waves of dog fighters planes, and unleash pixel-powered justice. Perfect for fans of Touhou, Ikaruga, or Raiden-style arcade games.

---

## 🛠️ Build Instructions

### 📦 Requirements
- CMake 3.17+
- C++ compiler (MSVC, Clang, or GCC)
- Raylib (installed via cmake)
- Dear ImGui (installed via cmake)

### 💻 Native Build (Windows/macOS/Linux)
```bash
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build