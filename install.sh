#!/bin/bash
set -e

echo "🚀 Dynamic Bar Installation"
echo "============================"

if [ "$EUID" -ne 0 ]; then
    echo "❌ This script must be run as root. Run with: sudo ./install.sh"
    exit 1
fi

echo "📦 Detecting package manager..."
if command -v pacman &> /dev/null; then
    echo "✓ Detected Arch/CachyOS (pacman)"
    PKG_MANAGER="pacman"
    DEPS="qt6-base qt6-declarative qt6-tools cmake gcc make"
    pacman -Syu
    pacman -S --noconfirm $DEPS
elif command -v dnf &> /dev/null; then
    echo "✓ Detected Fedora (dnf)"
    PKG_MANAGER="dnf"
    DEPS="qt6-qtbase qt6-qtdeclarative cmake gcc-c++ make"
    dnf check-update
    dnf install -y $DEPS
elif command -v apt &> /dev/null; then
    echo "✓ Detected Debian/Ubuntu (apt)"
    PKG_MANAGER="apt"
    DEPS="qt6-base-dev qt6-declarative-dev cmake g++ make"
    apt update
    apt install -y $DEPS
else
    echo "❌ No supported package manager found. Install Qt6 manually."
    exit 1
fi

echo ""
echo "🛠️  Building Dynamic Bar..."
cd "$(dirname "$0")"
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -j$(nproc)

echo ""
echo "📍 Installing..."
cmake --install .

echo ""
echo "⚙️  Setting up autostart..."
mkdir -p /etc/xdg/autostart
cp ../packaging/dynamic-bar-autostart.desktop /etc/xdg/autostart/

echo ""
echo "✨ Installation complete!"
echo "Dynamic Bar is ready. Start it with: dynamic-bar"
echo "To enable autostart, copy to ~/.config/autostart/dynamic-bar-autostart.desktop"
