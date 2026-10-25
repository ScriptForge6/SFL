#!/usr/bin/env bash
# Copyright 2026 Scriptforge
# Licensed under the Apache License, Version 2.0

set -euo pipefail

if [[ "$(uname -s)" != "Linux" ]]; then
    echo "[gtk] not Linux, skip"
    exit 0
fi

# 已经能找到就跳过
if pkg-config --exists gtk+-3.0 webkit2gtk-4.1 2>/dev/null; then
    echo "[gtk] gtk+-3.0 and webkit2gtk-4.1 already installed, skip"
    exit 0
fi

SUDO=""
[[ $EUID -ne 0 ]] && SUDO="sudo"

. /etc/os-release
case "${ID:-}:${ID_LIKE:-}" in
    debian:*|ubuntu:*|*:*debian*|*:*ubuntu*)
        $SUDO apt-get update
        $SUDO apt-get install -y build-essential pkg-config libgtk-3-dev libwebkit2gtk-4.1-dev
        ;;
    fedora:*|*:*fedora*|rhel:*|*:*rhel*)
        $SUDO dnf install -y gcc-c++ pkgconf-pkg-config gtk3-devel webkit2gtk4.1-devel
        ;;
    *)
        echo "[gtk] unsupported distro: ${ID:-unknown}. Please install GTK3 and WebKitGTK 4.1 dev packages manually." >&2
        exit 1
        ;;
esac

echo "[gtk] done"