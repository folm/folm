
Debian
====================
This directory contains files used to package folmd/folm-qt
for Debian-based Linux systems. If you compile folmd/folm-qt yourself, there are some useful files here.

## folm: URI support ##


folm-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install folm-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your folmqt binary to `/usr/bin`
and the `../../share/pixmaps/folm128.png` to `/usr/share/pixmaps`

folm-qt.protocol (KDE)

