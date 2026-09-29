# Dynamic Bar

A fast, keyboard-first QML desktop shell/pill bar for CachyOS and other Linux desktops. The repository now contains a buildable Qt 6 application with a transparent always-on-top dynamic pill, persistent JSON settings, profiles, launcher, control center, clipboard panel, and settings panel.

## Build

Dependencies: Qt 6.5+ (`Core Gui Qml Quick QuickControls2 DBus`), CMake 3.21+, and a C++20 compiler.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
./build/dynamic-bar
```

Install and autostart:

```bash
sudo cmake --install build
mkdir -p ~/.config/autostart
cp packaging/dynamic-bar-autostart.desktop ~/.config/autostart/
```

## Configuration

Settings persist at `~/.config/dynamic-bar/config.json`. Profiles, accent color, opacity, animation preference, module visibility, and dimensions are already represented in the configuration API. The C++/QML boundary is deliberately small so system backends can be added without changing the UI.

## Keyboard foundation

The application handles Escape, Ctrl+1..4, and panel navigation while focused. Desktop-wide Super bindings are compositor-specific on Wayland: bind `dynamic-bar` actions through KDE/KWin, Hyprland, Sway, or your window manager. The controller exposes panel/profile/power actions for the global shortcut backend to call.

## Roadmap

The modular UI is ready for native DBus backends for MPRIS, NetworkManager, BlueZ, `org.freedesktop.Notifications`, clipboard history, portals, and hardware sensors. These should be event-driven and injected as models rather than implemented as polling in QML.
